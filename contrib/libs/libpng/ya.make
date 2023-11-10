# Generated by devtools/yamaker from nixpkgs 22.11.

LIBRARY()

LICENSE(
    Libpng AND
    libpng-2.0
)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

VERSION(1.6.40)

ORIGINAL_SOURCE(https://github.com/glennrp/libpng/archive/v1.6.40.tar.gz)

PEERDIR(
    contrib/libs/zlib
)

ADDINCL(
    contrib/libs/libpng
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

SRCS(
    intel/filter_sse2_intrinsics.c
    intel/intel_init.c
    mips/filter_msa_intrinsics.c
    mips/mips_init.c
    png.c
    pngerror.c
    pngget.c
    pngmem.c
    pngpread.c
    pngread.c
    pngrio.c
    pngrtran.c
    pngrutil.c
    pngset.c
    pngtrans.c
    pngwio.c
    pngwrite.c
    pngwtran.c
    pngwutil.c
    powerpc/filter_vsx_intrinsics.c
    powerpc/powerpc_init.c
)

IF (NOT MSVC)
    IF (ARCH_AARCH64 OR ARCH_ARM)
        SRCS(
            arm/arm_init.c
            arm/filter_neon.S
            arm/filter_neon_intrinsics.c
            arm/palette_neon_intrinsics.c
        )
    ENDIF()
ENDIF()

END()

RECURSE(
    include
)
