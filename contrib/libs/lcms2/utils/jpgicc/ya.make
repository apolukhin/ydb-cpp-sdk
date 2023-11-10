# Generated by devtools/yamaker.

PROGRAM()

LICENSE(
    IJG AND
    MIT
)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

PEERDIR(
    contrib/libs/lcms2
    contrib/libs/libjpeg-turbo
)

ADDINCL(
    contrib/libs/lcms2/include
    contrib/libs/lcms2/utils/common
    contrib/libs/lcms2/utils/jpgicc
    contrib/libs/libjpeg-turbo
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

CFLAGS(
    -DHAVE_DLFCN_H=1
    -DHAVE_FUNC_ATTRIBUTE_VISIBILITY=1
    -DHAVE_GMTIME_R=1
    -DHAVE_INTTYPES_H=1
    -DHAVE_MEMORY_H=1
    -DHAVE_PTHREAD=1
    -DHAVE_PTHREAD_PRIO_INHERIT=1
    -DHAVE_STDINT_H=1
    -DHAVE_STDLIB_H=1
    -DHAVE_STRINGS_H=1
    -DHAVE_STRING_H=1
    -DHAVE_SYS_STAT_H=1
    -DHAVE_SYS_TYPES_H=1
    -DHAVE_TIFFCONF_H=1
    -DHAVE_UNISTD_H=1
    -DHasJPEG=1
    -DHasTHREADS=1
    -DHasTIFF=1
    -DHasZLIB=1
    -DLT_OBJDIR=\".libs/\"
)

SRCDIR(contrib/libs/lcms2/utils)

SRCS(
    common/vprf.c
    common/xgetopt.c
    jpgicc/iccjpeg.c
    jpgicc/jpgicc.c
)

END()
