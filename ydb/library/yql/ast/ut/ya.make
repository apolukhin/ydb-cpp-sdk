UNITTEST_FOR(ydb/library/yql/ast)

OWNER(vvvv g:kikimr)

FORK_SUBTESTS()

SRCS(
    yql_ast_ut.cpp
    yql_expr_check_args_ut.cpp 
    yql_expr_builder_ut.cpp
    yql_expr_ut.cpp
    yql_type_string_ut.cpp
)

PEERDIR(
)

END()
