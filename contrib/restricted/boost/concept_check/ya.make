# Generated by devtools/yamaker from nixpkgs 22.11.

LIBRARY()

LICENSE(BSL-1.0)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

VERSION(1.83.0)

ORIGINAL_SOURCE(https://github.com/boostorg/concept_check/archive/boost-1.83.0.tar.gz)

PEERDIR(
    contrib/restricted/boost/config
    contrib/restricted/boost/preprocessor
    contrib/restricted/boost/static_assert
    contrib/restricted/boost/type_traits
)

ADDINCL(
    GLOBAL contrib/restricted/boost/concept_check/include
)

NO_COMPILER_WARNINGS()

NO_UTIL()

END()
