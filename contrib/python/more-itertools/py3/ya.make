# Generated by devtools/yamaker (pypi).

PY3_LIBRARY()

VERSION(10.1.0)

LICENSE(MIT)

NO_LINT()

PY_SRCS(
    TOP_LEVEL
    more_itertools/__init__.py
    more_itertools/__init__.pyi
    more_itertools/more.py
    more_itertools/more.pyi
    more_itertools/recipes.py
    more_itertools/recipes.pyi
)

RESOURCE_FILES(
    PREFIX contrib/python/more-itertools/py3/
    .dist-info/METADATA
    .dist-info/top_level.txt
    more_itertools/py.typed
)

END()

RECURSE_FOR_TESTS(
    tests
)
