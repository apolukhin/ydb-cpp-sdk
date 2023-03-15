# Generated by devtools/yamaker from nixpkgs 22.05.

LIBRARY()

LICENSE(BSL-1.0)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

OWNER(
    g:cpp-contrib
    g:taxi-common
)

VERSION(1.81.0)

ORIGINAL_SOURCE(https://github.com/boostorg/heap/archive/boost-1.81.0.tar.gz)

PEERDIR(
    contrib/restricted/boost/array
    contrib/restricted/boost/assert
    contrib/restricted/boost/bind
    contrib/restricted/boost/concept_check
    contrib/restricted/boost/config
    contrib/restricted/boost/core
    contrib/restricted/boost/intrusive
    contrib/restricted/boost/iterator
    contrib/restricted/boost/parameter
    contrib/restricted/boost/static_assert
    contrib/restricted/boost/throw_exception
    contrib/restricted/boost/type_traits
)

ADDINCL(
    GLOBAL contrib/restricted/boost/heap/include
)

NO_COMPILER_WARNINGS()

NO_UTIL()

END()
