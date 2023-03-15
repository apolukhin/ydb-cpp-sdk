# Generated by devtools/yamaker from nixpkgs 22.05.

LIBRARY()

LICENSE(BSL-1.0)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

OWNER(
    g:cpp-contrib
    g:taxi-common
)

VERSION(1.81.0)

ORIGINAL_SOURCE(https://github.com/boostorg/functional/archive/boost-1.81.0.tar.gz)

PEERDIR(
    contrib/restricted/boost/config
    contrib/restricted/boost/core
    contrib/restricted/boost/function
    contrib/restricted/boost/function_types
    contrib/restricted/boost/mpl
    contrib/restricted/boost/preprocessor
    contrib/restricted/boost/type_traits
    contrib/restricted/boost/typeof
    contrib/restricted/boost/utility
)

ADDINCL(
    GLOBAL contrib/restricted/boost/functional/include
)

NO_COMPILER_WARNINGS()

NO_UTIL()

END()
