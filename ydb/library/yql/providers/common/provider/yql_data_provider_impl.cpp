#include "yql_data_provider_impl.h"

#include <ydb/library/yql/core/yql_expr_constraint.h>

#include <util/system/compiler.h>

namespace NYql {

void TPlanFormatterBase::WriteDetails(const TExprNode& node, NYson::TYsonWriter& writer) {
    Y_UNUSED(node);
    Y_UNUSED(writer);
}

bool TPlanFormatterBase::GetDependencies(const TExprNode& node, TExprNode::TListType& children, bool compact) {
    Y_UNUSED(node);
    Y_UNUSED(children);
    Y_UNUSED(compact);
    return false;
}

void TPlanFormatterBase::GetResultDependencies(const TExprNode::TPtr& node, TExprNode::TListType& children, bool compact) {
    Y_UNUSED(node);
    Y_UNUSED(children);
    Y_UNUSED(compact);
}

void TPlanFormatterBase::GetInputs(const TExprNode& node, TVector<TPinInfo>& inputs) {
    Y_UNUSED(node);
    Y_UNUSED(inputs);
}

void TPlanFormatterBase::GetOutputs(const TExprNode& node, TVector<TPinInfo>& outputs) {
    Y_UNUSED(node);
    Y_UNUSED(outputs);
}

TString TPlanFormatterBase::GetProviderPath(const TExprNode& node) {
    Y_UNUSED(node);
    return TString();
}

void TPlanFormatterBase::WritePlanDetails(const TExprNode& node, NYson::TYsonWriter& writer) {
    Y_UNUSED(node);
    Y_UNUSED(writer);
}

void TPlanFormatterBase::WritePullDetails(const TExprNode& node, NYson::TYsonWriter& writer) {
    Y_UNUSED(node);
    Y_UNUSED(writer);
}

void TPlanFormatterBase::WritePinDetails(const TExprNode& node, NYson::TYsonWriter& writer) {
    Y_UNUSED(node);
    Y_UNUSED(writer);
}

TString TPlanFormatterBase::GetOperationDisplayName(const TExprNode& node) {
    return TString(node.Content());
}

void TTrackableNodeProcessorBase::GetUsedNodes(const TExprNode& node, TVector<TString>& usedNodeIds) { 
    Y_UNUSED(node); 
    usedNodeIds.clear(); 
} 
 
void TTrackableNodeProcessorBase::GetCreatedNodes(const TExprNode& node, TVector<TExprNodeAndId>& createdNodes, TExprContext& ctx) { 
    Y_UNUSED(node); 
    Y_UNUSED(ctx); 
    createdNodes.clear(); 
} 
 
IGraphTransformer& TTrackableNodeProcessorBase::GetCleanupTransformer() { 
    return NullTransformer_; 
} 
 
bool TDataProviderBase::Initialize(TExprContext& ctx) {
    Y_UNUSED(ctx);
    return true;
}

IGraphTransformer& TDataProviderBase::GetConfigurationTransformer() {
    return NullTransformer_;
}

TExprNode::TPtr TDataProviderBase::GetClusterInfo(const TString& cluster, TExprContext& ctx) {
    Y_UNUSED(cluster);
    Y_UNUSED(ctx);
    return {};
}

const THashMap<TString, TString>* TDataProviderBase::GetClusterTokens() {
    return nullptr;
}

IGraphTransformer& TDataProviderBase::GetIODiscoveryTransformer() {
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetEpochsTransformer() {
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetIntentDeterminationTransformer() {
    return NullTransformer_;
}

bool TDataProviderBase::ValidateParameters(TExprNode& node, TExprContext& ctx, TMaybe<TString>& cluster) {
    Y_UNUSED(node);
    Y_UNUSED(ctx);

    cluster = Nothing();
    return true;
}

bool TDataProviderBase::CanParse(const TExprNode& node) {
    Y_UNUSED(node);
    return false;
}

void TDataProviderBase::FillModifyCallables(THashSet<TStringBuf>& callables) {
    Y_UNUSED(callables);
}

IGraphTransformer& TDataProviderBase::GetTypeAnnotationTransformer(bool instantOnly) {
    Y_UNUSED(instantOnly);
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetConstraintTransformer(bool instantOnly, bool subGraph) {
    Y_UNUSED(instantOnly);
    Y_UNUSED(subGraph);
    if (!DefConstraintTransformer_) {
        DefConstraintTransformer_ = CreateDefCallableConstraintTransformer();
    }
    return *DefConstraintTransformer_;
}

TExprNode::TPtr TDataProviderBase::RewriteIO(const TExprNode::TPtr& node, TExprContext& ctx) {
    Y_UNUSED(ctx);
    return node;
}

void TDataProviderBase::PostRewriteIO() {
}

void TDataProviderBase::Reset() {
    GetConfigurationTransformer().Rewind();
    GetIODiscoveryTransformer().Rewind();
    GetEpochsTransformer().Rewind();
    GetIntentDeterminationTransformer().Rewind();
    for (auto flag : {true, false}) {
        GetTypeAnnotationTransformer(flag).Rewind();
    }
    for (auto flag1 : {true, false}) {
        for (auto flag2 : {true, false}) {
            GetConstraintTransformer(flag1, flag2).Rewind();
        }
    }
    GetRecaptureOptProposalTransformer().Rewind();
    GetLogicalOptProposalTransformer().Rewind();
    GetPhysicalOptProposalTransformer().Rewind();
    GetPhysicalFinalizingTransformer().Rewind();
    GetLoadTableMetadataTransformer().Rewind();
    GetCallableExecutionTransformer().Rewind();
    GetFinalizingTransformer().Rewind();
    GetPlanInfoTransformer().Rewind();
    GetTrackableNodeProcessor().GetCleanupTransformer().Rewind();
}

IGraphTransformer& TDataProviderBase::GetRecaptureOptProposalTransformer() {
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetLogicalOptProposalTransformer() {
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetPhysicalOptProposalTransformer() {
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetPhysicalFinalizingTransformer() {
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetLoadTableMetadataTransformer() {
    return NullTransformer_;
}

bool TDataProviderBase::IsPersistent(const TExprNode& node) {
    Y_UNUSED(node);
    return false;
}

bool TDataProviderBase::CanBuildResult(const TExprNode& node, TSyncMap& syncList) {
    Y_UNUSED(node);
    Y_UNUSED(syncList);
    return false;
}

bool TDataProviderBase::CanPullResult(const TExprNode& node, TSyncMap& syncList, bool& canRef) {
    Y_UNUSED(node);
    Y_UNUSED(syncList);
    Y_UNUSED(canRef);
    return false;
}

bool TDataProviderBase::GetExecWorld(const TExprNode& node, TExprNode::TPtr& root) {
    root = nullptr;
    Y_UNUSED(node);
    return false;
}

bool TDataProviderBase::CanEvaluate(const TExprNode& node) {
    Y_UNUSED(node);
    return false;
}

void TDataProviderBase::UndoEvaluationChanges() {
    GetCallableExecutionTransformer().Rewind();
    GetEpochsTransformer().Rewind();
}

TExprNode::TPtr TDataProviderBase::CleanupWorld(const TExprNode::TPtr& node, TExprContext& ctx) {
    Y_UNUSED(ctx);
    return node;
}

TExprNode::TPtr TDataProviderBase::OptimizePull(const TExprNode::TPtr& source, const TFillSettings& fillSettings,
    TExprContext& ctx, IOptimizationContext& optCtx)
{
    Y_UNUSED(fillSettings);
    Y_UNUSED(ctx);
    Y_UNUSED(optCtx);
    return source;

}

bool TDataProviderBase::CanExecute(const TExprNode& node) {
    Y_UNUSED(node);
    return false;
}

void TDataProviderBase::GetRequiredChildren(const TExprNode& node, TExprNode::TListType& children) {
    TPlanFormatterBase::GetDependencies(node, children, false);
}

IGraphTransformer& TDataProviderBase::GetCallableExecutionTransformer() {
    return NullTransformer_;
}

IGraphTransformer& TDataProviderBase::GetFinalizingTransformer() {
    return NullTransformer_;
}

bool TDataProviderBase::CollectDiagnostics(NYson::TYsonWriter& writer) {
    Y_UNUSED(writer);
    return false;
}

bool TDataProviderBase::GetTasksInfo(NYson::TYsonWriter& writer) {
    Y_UNUSED(writer);
    return false;
}

bool TDataProviderBase::CollectStatistics(NYson::TYsonWriter& writer, bool totalOnly) {
    Y_UNUSED(writer);
    Y_UNUSED(totalOnly);
    return false;
}

bool TDataProviderBase::CollectDiscoveredData(NYson::TYsonWriter& writer) {
    Y_UNUSED(writer);
    return false;
}

IPlanFormatter& TDataProviderBase::GetPlanFormatter() {
    return *this;
}

ITrackableNodeProcessor& TDataProviderBase::GetTrackableNodeProcessor() { 
    return NullTrackableNodeProcessor_; 
} 
 
IGraphTransformer& TDataProviderBase::GetPlanInfoTransformer() {
    return NullTransformer_;
}

IDqIntegration* TDataProviderBase::GetDqIntegration() {
    return nullptr;
}

} // namespace NYql
