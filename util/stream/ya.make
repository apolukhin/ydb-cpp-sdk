SUBSCRIBER(g:util-subscribers)

RECURSE_FOR_TESTS(
    ut
)

IF (NOT OS_IOS AND NOT OS_ANDROID AND NOT USE_SYSTEM_PYTHON)
    RECURSE(
        ut_cython
    )
ENDIF()
