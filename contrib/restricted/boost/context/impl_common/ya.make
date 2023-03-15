# Generated by devtools/yamaker.

LIBRARY()

WITHOUT_LICENSE_TEXTS()

OWNER(
    g:cpp-contrib
    g:taxi-common
)

VERSION(1.81.0)

ORIGINAL_SOURCE(https://github.com/boostorg/context/archive/boost-1.81.0.tar.gz)

LICENSE(BSL-1.0)

PEERDIR(
    contrib/restricted/boost/assert
    contrib/restricted/boost/config
    contrib/restricted/boost/core
    contrib/restricted/boost/mp11
    contrib/restricted/boost/pool
    contrib/restricted/boost/predef
    contrib/restricted/boost/smart_ptr
)

ADDINCL(
    GLOBAL contrib/restricted/boost/context/include
)

NO_COMPILER_WARNINGS()

NO_UTIL()

CFLAGS(
    -DBOOST_CONTEXT_SOURCE
)

IF (DYNAMIC_BOOST)
    CFLAGS(
        GLOBAL -DBOOST_CONTEXT_DYN_LINK
    )
ENDIF()

SRCDIR(contrib/restricted/boost/context/src)

IF (OS_WINDOWS)
    SRCS(
        windows/stack_traits.cpp
    )
ELSE()
    SRCS(
        posix/stack_traits.cpp
    )
ENDIF()

END()
