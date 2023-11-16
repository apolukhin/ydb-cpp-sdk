# Generated by devtools/yamaker (pypi).

PY3_LIBRARY()

VERSION(0.22.0)

LICENSE(BSD-3-Clause)

PEERDIR(
    contrib/libs/zstd
)

ADDINCL(
    contrib/libs/zstd/include
    contrib/python/zstandard/py3/c-ext
)

NO_COMPILER_WARNINGS()

NO_LINT()

SRCS(
    c-ext/backend_c.c
    c-ext/bufferutil.c
    c-ext/compressionchunker.c
    c-ext/compressiondict.c
    c-ext/compressionparams.c
    c-ext/compressionreader.c
    c-ext/compressionwriter.c
    c-ext/compressobj.c
    c-ext/compressor.c
    c-ext/compressoriterator.c
    c-ext/constants.c
    c-ext/decompressionreader.c
    c-ext/decompressionwriter.c
    c-ext/decompressobj.c
    c-ext/decompressor.c
    c-ext/decompressoriterator.c
    c-ext/frameparams.c
)

PY_REGISTER(
    zstandard.backend_c
)

PY_SRCS(
    TOP_LEVEL
    zstandard/__init__.py
    zstandard/__init__.pyi
)

RESOURCE_FILES(
    PREFIX contrib/python/zstandard/py3/
    .dist-info/METADATA
    .dist-info/top_level.txt
    zstandard/py.typed
)

END()
