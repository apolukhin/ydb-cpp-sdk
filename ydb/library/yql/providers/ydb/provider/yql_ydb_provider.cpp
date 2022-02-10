#include "yql_ydb_provider.h"
#include <ydb/library/yql/providers/common/proto/gateways_config.pb.h> 
#include <ydb/library/yql/providers/common/provider/yql_provider_names.h> 

namespace NYql {

TDataProviderInitializer GetYdbDataProviderInitializer(
    NYdb::TDriver driver,
    ISecuredServiceAccountCredentialsFactory::TPtr credentialsFactory,
    std::shared_ptr<NYq::TDatabaseAsyncResolverWithMeta> dbResolverWithMeta) {
    return [driver, credentialsFactory, dbResolverWithMeta] (
        const TString& userName,
        const TString& sessionId,
        const TGatewaysConfig* gatewaysConfig,
        const NKikimr::NMiniKQL::IFunctionRegistry* functionRegistry,
        TIntrusivePtr<IRandomProvider> randomProvider,
        TIntrusivePtr<TTypeAnnotationContext> typeCtx,
        const TOperationProgressWriter& progressWriter,
        const TYqlOperationOptions& operationOptions)
    {
        Y_UNUSED(sessionId);
        Y_UNUSED(userName);
        Y_UNUSED(functionRegistry);
        Y_UNUSED(randomProvider);
        Y_UNUSED(progressWriter);
        Y_UNUSED(operationOptions);

        auto state = MakeIntrusive<TYdbState>();

        state->Types = typeCtx.Get();
        state->FunctionRegistry = functionRegistry;
        state->CredentialsFactory = credentialsFactory;
        state->DbResolver = dbResolverWithMeta;
        if (gatewaysConfig) {
            state->Configuration->Init(gatewaysConfig->GetYdb(), typeCtx, state->DbResolver, state->DatabaseIds);
        }

        TDataProviderInfo info;

        info.Names.insert({TString{YdbProviderName}});
        info.Source = CreateYdbDataSource(state, driver);
        info.Sink = CreateYdbDataSink(state);

        return info;
    };
}

} // namespace NYql
