# Generated by devtools/yamaker (pypi).

PY3_LIBRARY()

VERSION(1.1.0)

LICENSE(BSD-3-Clause)

PEERDIR(
    contrib/python/setuptools
)

ADDINCL(
    contrib/python/kiwisolver/py3
)

NO_COMPILER_WARNINGS()

NO_LINT()

SRCS(
    py/constraint.cpp
    py/expression.cpp
    py/kiwisolver.cpp
    py/solver.cpp
    py/strength.cpp
    py/term.cpp
    py/variable.cpp
)

PY_REGISTER(
    kiwisolver
)

RESOURCE_FILES(
    PREFIX contrib/python/kiwisolver/py3/
    .dist-info/METADATA
    .dist-info/top_level.txt
)

END()
