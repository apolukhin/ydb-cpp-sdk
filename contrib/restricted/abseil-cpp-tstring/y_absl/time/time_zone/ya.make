# Generated by devtools/yamaker.

LIBRARY()

WITHOUT_LICENSE_TEXTS()

OWNER(
    somov
    g:cpp-contrib
)

LICENSE(Apache-2.0)

ADDINCL(
    GLOBAL contrib/restricted/abseil-cpp-tstring
)

IF (OS_DARWIN)
    EXTRALIBS("-framework CoreFoundation")
ENDIF()

NO_COMPILER_WARNINGS()

SRCDIR(contrib/restricted/abseil-cpp-tstring/y_absl/time/internal/cctz/src)

SRCS(
    time_zone_fixed.cc
    time_zone_format.cc
    time_zone_if.cc
    time_zone_impl.cc
    time_zone_info.cc
    time_zone_libc.cc
    time_zone_lookup.cc
    time_zone_posix.cc
    zone_info_source.cc
)

END()
