# Generated by devtools/yamaker.

LIBRARY()

LICENSE(BSD-3-Clause)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

ADDINCL(
    ${ARCADIA_BUILD_ROOT}/contrib/libs/grpc
    contrib/libs/grpc
    contrib/libs/grpc/src/core/ext/upb-generated
    contrib/libs/grpc/src/core/ext/upbdefs-generated
    contrib/libs/grpc/third_party/upb
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

SRCDIR(contrib/libs/grpc)

IF (OS_LINUX OR OS_DARWIN)
    CFLAGS(
        -DGRPC_POSIX_FORK_ALLOW_PTHREAD_ATFORK=1
    )
ENDIF()

SRCS(
    src/core/ext/upb-generated/google/protobuf/descriptor.upb.c
    src/core/ext/upbdefs-generated/google/protobuf/descriptor.upbdefs.c
    third_party/upb/upb/decode.c
    third_party/upb/upb/decode_fast.c
    third_party/upb/upb/def.c
    third_party/upb/upb/encode.c
    third_party/upb/upb/msg.c
    third_party/upb/upb/reflection.c
    third_party/upb/upb/table.c
    third_party/upb/upb/text_encode.c
    third_party/upb/upb/upb.c
)

END()
