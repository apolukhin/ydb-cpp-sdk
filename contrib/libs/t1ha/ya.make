# Generated by devtools/yamaker from nixpkgs 22.05.

LIBRARY()

LICENSE(Zlib)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

VERSION(2.1.4)

ORIGINAL_SOURCE(https://github.com/PositiveTechnologies/t1ha/archive/v2.1.4.tar.gz)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

SRCS(
    src/t1ha0.c
    src/t1ha0_ia32aes_avx.c
    src/t1ha0_ia32aes_avx2.c
    src/t1ha0_ia32aes_noavx.c
    src/t1ha0_selfcheck.c
    src/t1ha1.c
    src/t1ha1_selfcheck.c
    src/t1ha2.c
    src/t1ha2_selfcheck.c
    src/t1ha_selfcheck.c
    src/t1ha_selfcheck_all.c
)

IF (ARCH_X86_64)
    CFLAGS(
        -maes
    )
ENDIF()

END()
