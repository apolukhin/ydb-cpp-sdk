# Generated by devtools/yamaker from nixpkgs 22.05.

LIBRARY()

LICENSE(MIT)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

VERSION(0.2.5)

ORIGINAL_SOURCE(https://github.com/yaml/libyaml/archive/0.2.5.tar.gz)

ADDINCL(
    GLOBAL contrib/libs/yaml/include
    contrib/libs/yaml/src
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

CFLAGS(
    -DHAVE_CONFIG_H
)

SRCS(
    src/api.c
    src/dumper.c
    src/emitter.c
    src/loader.c
    src/parser.c
    src/reader.c
    src/scanner.c
    src/writer.c
)

END()
