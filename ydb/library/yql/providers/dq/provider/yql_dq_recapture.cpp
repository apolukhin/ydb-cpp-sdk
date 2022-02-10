#include "yql_dq_state.h"
#include "yql_dq_provider.h"

#include <ydb/library/yql/providers/common/provider/yql_provider_names.h>
#include <ydb/library/yql/providers/dq/expr_nodes/dqs_expr_nodes.h>
#include <ydb/library/yql/providers/dq/interface/yql_dq_integration.h>
#include <ydb/library/yql/core/expr_nodes/yql_expr_nodes.h>
#include <ydb/library/yql/core/yql_expr_optimize.h>
#include <ydb/library/yql/core/yql_graph_transformer.h>
#include <ydb/library/yql/core/yql_expr_type_annotation.h>
#include <ydb/library/yql/core/yql_opt_utils.h>
#include <ydb/library/yql/ast/yql_expr.h>
#include <ydb/library/yql/utils/log/log.h>
#include <ydb/library/yql/dq/opt/dq_opt.h>

#include <util/generic/scope.h>

namespace NYql {

using namespace NNodes;

namespace {

const THashSet<TStringBuf> VALID_SOURCES = {DqProviderName, ConfigProviderName, YtProviderName, ClickHouseProviderName, YdbProviderName};
const THashSet<TStringBuf> VALID_SINKS = {ResultProviderName, YtProviderName};
const THashSet<TStringBuf> UNSUPPORTED_CALLABLE = { TCoForwardList::CallableName() };

}

namespace NDq {
    bool CheckJoinColumns(const TExprBase& node);
    bool CheckJoinLinkSettings(const TExprBase& node);
} // namespace NDq

class TDqsRecaptureTransformer : public TSyncTransformerBase {
public:
    TDqsRecaptureTransformer(TDqStatePtr state)
        : State_(state)
    {
    }

    TStatus DoTransform(TExprNode::TPtr input, TExprNode::TPtr& output, TExprContext& ctx) final {
        output = input;
        if (ctx.Step.IsDone(TExprStep::Recapture)) {
            return TStatus::Ok;
        }

        Y_SCOPE_EXIT(&) {
            FlushStatistics();
        };

        if (State_->ExternalUser) {
            Statistics_["DqExternalUser"]++;
            return TStatus::Ok;
        }

        if (State_->TypeCtx->ForceDq) {
            Statistics_["DqForce"]++;
        }

        if (!State_->TypeCtx->ForceDq) {
            if (!State_->Settings->AnalyzeQuery.Get().GetOrElse(false)) {
                Statistics_["DqAnalyzerOff"]++;
            }

            if (State_->TypeCtx->PureResultDataSource != DqProviderName) {
                Statistics_["DqPureResultDataSourceMismatch"]++;
            }

            if (State_->TypeCtx->PureResultDataSource != DqProviderName || !State_->Settings->AnalyzeQuery.Get().GetOrElse(false)) {
                return TStatus::Ok;
            }

            Statistics_["DqAnalyzerOn"]++;

            ui64 dataSize = 0;
            bool good = true;
            bool hasJoin = false;
            TNodeSet visited;
            Scan(*input, ctx, good, dataSize, visited, hasJoin);

            if (good) {
                Statistics_["DqAnalyzerOk"]++;
            } else {
                Statistics_["DqAnalyzerFail"] ++;
            }

            if ((hasJoin && dataSize > State_->Settings->MaxDataSizePerQuery.Get().GetOrElse(10_GB))) {
                Statistics_["DqAnalyzerBigJoin"]++;
            }

            if (!good || (hasJoin && dataSize > State_->Settings->MaxDataSizePerQuery.Get().GetOrElse(10_GB))) {
                YQL_LOG(DEBUG) << "good: " << good << " hasJoin: " << hasJoin << " dataSize: " << dataSize;
                return TStatus::Ok;
            }
        }

        State_->TypeCtx->DqFallbackPolicy = State_->Settings->FallbackPolicy.Get().GetOrElse("default");

        auto status = OptimizeExpr(input, output, [&](const TExprNode::TPtr& node, TExprContext& ctx) {
            if (auto maybeRead = TMaybeNode<TCoRight>(node).Input()) {
                if (maybeRead.Raw()->ChildrenSize() > 1 && TCoDataSource::Match(maybeRead.Raw()->Child(1))) {
                    auto dataSourceName = maybeRead.Raw()->Child(1)->Child(0)->Content();
                    auto dataSource = State_->TypeCtx->DataSourceMap.FindPtr(dataSourceName);
                    YQL_ENSURE(dataSource);
                    if (auto dqIntegration = (*dataSource)->GetDqIntegration()) {
                        auto newRead = dqIntegration->WrapRead(*State_->Settings, maybeRead.Cast().Ptr(), ctx);
                        if (newRead.Get() != maybeRead.Raw()) {
                            return newRead;
                        }
                    }
                }
            }

            return node;
        }, ctx, TOptimizeExprSettings{State_->TypeCtx});

        if (input != output) {
            // TODO: Add before/after recapture transformers
            State_->TypeCtx->DqCaptured = true;
            // TODO: drop this after implementing DQS ConstraintTransformer
            State_->TypeCtx->ExpectedConstraints.clear();
        }
        return status;
    }

    void Rewind() final {
    }

private:
    void AddInfo(TExprContext& ctx, const TString& message) const {
        YQL_LOG(DEBUG) << message;
        TIssue info("DQ cannot execute the query. Cause: " + message);
        info.Severity = TSeverityIds::S_INFO;
        ctx.IssueManager.RaiseIssue(info);
    }

    void Scan(const TExprNode& node, TExprContext& ctx, bool& good, ui64& dataSize, TNodeSet& visited, bool& hasJoin) const {
        if (!visited.insert(&node).second) {
            return;
        }

        TExprBase expr(&node);
        if (TMaybeNode<TCoEquiJoin>(&node)) {
            hasJoin = true;
        }

        if (TCoCommit::Match(&node)) {
            for (size_t i = 0; i != node.ChildrenSize() && good; ++i) {
                if (i != TCoCommit::idx_DataSink) {
                    Scan(*node.Child(i), ctx, good, dataSize, visited, hasJoin);
                }
            }
        } else if (node.IsCallable(UNSUPPORTED_CALLABLE)) {
            AddInfo(ctx, TStringBuilder() << "unsupported callable '" << node.Content() << "'");
            good = false;
        } else if (node.IsCallable(TCoCollect::CallableName())) {
            if (ETypeAnnotationKind::List != node.Head().GetTypeAnn()->GetKind()) {
                AddInfo(ctx, TStringBuilder() << "unsupported callable '" << node.Content() << "' over stream/flow");
                good = false;
            }
        } else if (auto datasource = TMaybeNode<TCoDataSource>(&node).Category()) {
            if (!VALID_SOURCES.contains(datasource.Cast().Value())) {
                AddInfo(ctx, TStringBuilder() << "source '" << datasource.Cast().Value() << "' is not supported by DQ");
                good = false;
            }
        } else if (auto datasink = TMaybeNode<TCoDataSink>(&node).Category()) {
            if (!VALID_SINKS.contains(datasink.Cast().Value())) {
                AddInfo(ctx, TStringBuilder() << "sink '" << datasink.Cast().Value() << "' is not supported by DQ");
                good = false;
            }
        } else if (TMaybeNode<TCoEquiJoin>(&node) && !NDq::CheckJoinColumns(expr)) {
            AddInfo(ctx, TStringBuilder() << "unsupported join column");
            good = false;
        } else if (TMaybeNode<TCoEquiJoin>(&node) && !NDq::CheckJoinLinkSettings(expr)) {
            AddInfo(ctx, TStringBuilder() << "unsupported join any");
            good = false;
        } else if (node.ChildrenSize() > 1 && TCoDataSource::Match(node.Child(1))) {
            auto dataSourceName = node.Child(1)->Child(0)->Content();
            if (dataSourceName != DqProviderName && !node.IsCallable(ConfigureName)) {
                auto datasource = State_->TypeCtx->DataSourceMap.FindPtr(dataSourceName);
                YQL_ENSURE(datasource);
                if (auto dqIntegration = (*datasource)->GetDqIntegration()) {
                    if (auto size = dqIntegration->CanRead(*State_->Settings, node, ctx, /*skipIssues = */ false)) {
                        dataSize += *size;
                    } else {
                        good = false;
                    }
                } else {
                    AddInfo(ctx, TStringBuilder() << "source '" << dataSourceName << "' is not supported by DQ");
                    good = false;
                }
            }

            if (good) {
                Scan(node.Head(), ctx,good, dataSize, visited, hasJoin);
            }
        } else if (node.GetTypeAnn()->GetKind() == ETypeAnnotationKind::World
            && !TCoCommit::Match(&node)
            && node.ChildrenSize() > 1
            && TCoDataSink::Match(node.Child(1))) {
            auto dataSinkName = node.Child(1)->Child(0)->Content();
            auto dataSink = State_->TypeCtx->DataSinkMap.FindPtr(dataSinkName);
            YQL_ENSURE(dataSink);
            if (auto dqIntegration = dataSink->Get()->GetDqIntegration()) {
                if (auto canWrite = dqIntegration->CanWrite(*State_->Settings, node, ctx)) {
                    if (!canWrite.GetRef()) {
                        good = false;
                    } else if (!State_->Settings->EnableInsert.Get().GetOrElse(false)) {
                        AddInfo(ctx, TStringBuilder() << "'insert' support is disabled. Use PRAGMA dq.EnableInsert to explicitly enable it");
                        good = false;
                    }
                }
            }
            if (good) {
                for (size_t i = 0; i != node.ChildrenSize() && good; ++i) {
                    Scan(*node.Child(i), ctx, good, dataSize, visited, hasJoin);
                }
            }
        }
        else if (!State_->TypeCtx->UdfSupportsYield && TCoScriptUdf::Match(&node)) {
            if (IsCallableTypeHasStreams(node.GetTypeAnn()->Cast<TCallableExprType>())) {
                AddInfo(ctx, TStringBuilder() << "script udf with streams");
                good = false;
            }
            if (good) {
                for (size_t i = 0; i != node.ChildrenSize() && good; ++i) {
                    Scan(*node.Child(i), ctx, good, dataSize, visited, hasJoin);
                }
            }
        }
        else {
            for (size_t i = 0; i != node.ChildrenSize() && good; ++i) {
                Scan(*node.Child(i), ctx, good, dataSize, visited, hasJoin);
            }
        }
    }

private:
    TDqStatePtr State_;

    THashMap<TString, int> Statistics_;

    void FlushStatistics() {
        TOperationStatistics statistics;
        for (const auto& [k, v] : Statistics_) {
            if (v == 1) {
                statistics.Entries.push_back(TOperationStatistics::TEntry(k, 0, 0, 0, 0, 1));
            }
        }

        TGuard<TMutex> lock(State_->Mutex);
        if (!statistics.Entries.empty()) {
            State_->Statistics[State_->MetricId++] = statistics;
        }
    }
};

THolder<IGraphTransformer> CreateDqsRecaptureTransformer(TDqStatePtr state) {
    return THolder(new TDqsRecaptureTransformer(state)); 
}

} // NYql
