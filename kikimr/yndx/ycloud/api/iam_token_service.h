#pragma once
#include <ydb/core/base/defs.h>
#include <ydb/core/base/events.h>
#include <yandex/cloud/priv/iam/v1/iam_token_service.grpc.pb.h>
#include "events.h"

namespace NCloud {
    using namespace NKikimr;

    class TIamTokenService;

    struct TEvIamTokenService {
        enum EEv {
            // requests
            EvCreateForServiceAccountRequest = EventSpaceBegin(TKikimrEvents::ES_IAM_TOKEN_SERVICE),

            // replies
            EvCreateResponse = EventSpaceBegin(TKikimrEvents::ES_IAM_TOKEN_SERVICE) + 1024,

            EvEnd
        };

        static_assert(EvEnd < EventSpaceEnd(TKikimrEvents::ES_IAM_TOKEN_SERVICE), "expect EvEnd < EventSpaceEnd(TKikimrEvents::ES_SERVICE_ACCOUNT_SERVICE)");

        // https://a.yandex-team.ru/arc/trunk/arcadia/cloud/bitbucket/private-api/yandex/cloud/priv/iam/v1/iam_token_service.proto

        struct TEvCreateForServiceAccountRequest : TEvGrpcProtoRequest<TEvCreateForServiceAccountRequest, EvCreateForServiceAccountRequest, yandex::cloud::priv::iam::v1::CreateIamTokenForServiceAccountRequest> {};
        struct TEvCreateResponse : TEvGrpcProtoResponse<TEvCreateResponse, EvCreateResponse, yandex::cloud::priv::iam::v1::CreateIamTokenResponse> {};
    };
}
