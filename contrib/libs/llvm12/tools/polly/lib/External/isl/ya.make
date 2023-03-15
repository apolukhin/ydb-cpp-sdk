# Generated by devtools/yamaker.

LIBRARY()

LICENSE(MIT)

LICENSE_TEXTS(.yandex_meta/licenses.list.txt)

ADDINCL(
    contrib/libs/llvm12/tools/polly/lib/External
    contrib/libs/llvm12/tools/polly/lib/External/isl
    contrib/libs/llvm12/tools/polly/lib/External/isl/imath
    contrib/libs/llvm12/tools/polly/lib/External/isl/include
)

NO_COMPILER_WARNINGS()

NO_RUNTIME()

SRCS(
    basis_reduction_tab.c
    imath/gmp_compat.c
    imath/imath.c
    imath/imrat.c
    isl_aff.c
    isl_aff_map.c
    isl_affine_hull.c
    isl_arg.c
    isl_ast.c
    isl_ast_build.c
    isl_ast_build_expr.c
    isl_ast_codegen.c
    isl_ast_graft.c
    isl_bernstein.c
    isl_blk.c
    isl_bound.c
    isl_box.c
    isl_coalesce.c
    isl_constraint.c
    isl_convex_hull.c
    isl_ctx.c
    isl_deprecated.c
    isl_dim_map.c
    isl_equalities.c
    isl_factorization.c
    isl_farkas.c
    isl_ffs.c
    isl_flow.c
    isl_fold.c
    isl_hash.c
    isl_id.c
    isl_id_to_ast_expr.c
    isl_id_to_id.c
    isl_id_to_pw_aff.c
    isl_ilp.c
    isl_imath.c
    isl_input.c
    isl_int_sioimath.c
    isl_local.c
    isl_local_space.c
    isl_lp.c
    isl_map.c
    isl_map_list.c
    isl_map_simplify.c
    isl_map_subtract.c
    isl_map_to_basic_set.c
    isl_mat.c
    isl_morph.c
    isl_obj.c
    isl_options.c
    isl_output.c
    isl_point.c
    isl_polynomial.c
    isl_printer.c
    isl_range.c
    isl_reordering.c
    isl_sample.c
    isl_scan.c
    isl_schedule.c
    isl_schedule_band.c
    isl_schedule_constraints.c
    isl_schedule_node.c
    isl_schedule_read.c
    isl_schedule_tree.c
    isl_scheduler.c
    isl_seq.c
    isl_set_list.c
    isl_set_to_ast_graft_list.c
    isl_sort.c
    isl_space.c
    isl_stream.c
    isl_stride.c
    isl_tab.c
    isl_tab_pip.c
    isl_tarjan.c
    isl_transitive_closure.c
    isl_union_map.c
    isl_val.c
    isl_val_sioimath.c
    isl_vec.c
    isl_version.c
    isl_vertices.c
    print.c
    set_from_map.c
    set_to_map.c
    uset_from_umap.c
    uset_to_umap.c
)

END()
