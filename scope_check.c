#include "scope_check.h"

void scope_check_program(block_t prog)
{
    scope_check_block(prog);
}

extern void scope_check_block(block_t blk) // why is it extern in the unparser?
{
    scope_check_const_decls(blk.const_decls);
    scope_check_var_decls(blk.var_decls);
    scope_check_proc_decls(blk.proc_decls);
    scope_check_stmt(blk.stmt);
}

void scope_check_const_decls(const_decls_t cds);
{

}

void scope_check_const_decl(const_decl_t cd);
{

}

void scope_check_const_defs(const_defs_t cdfs);
{

}

void scope_check_const_def(const_def_t cdf);
{

}

void scope_check_var_decls(var_decls_t vds);
{

}

void scope_check_var_decl(var_decl_t vd);
{

}

void scope_check_idents(idents_t idents);
{

}

void scope_check_proc_decls(proc_decls_t pds);
{

}

void scope_check_proc_decl(proc_decl_t pd);
{

}

void scope_check_stmts(stmts_t stmts);
{

}

void scope_check_stmt(stmt_t stmt);
{

}

void scope_check_assign_stmt(assign_stmt_t stmt);
{

}

void scope_check_call_stmt(call_stmt_t stmt);
{

}

void scope_check_begin_stmt(begin_stmt_t stmt);
{

}

void scope_check_if_stmt(if_stmt_t stmt);
{

}

void scope_check_while_stmt(while_stmt_t stmt);
{

}

void scope_check_read_stmt(read_stmt_t stmt);
{

}

void scope_check_write_stmt(write_stmt_t stmt);
{

}

void scope_check_skip_stmt(int level);
{

}

void scope_check_condition(condition_t cond);
{

}

void scope_check_odd_condition(odd_condition_t cond);
{

}

void scope_check_rel_op_condition(rel_op_condition_t cond);
{

}

void scope_check_token(token_t token);
{

}

void scope_check_expr(expr_t exp);
{

}

void scope_check_bin_op_expr(binary_op_expr_t exp);
{

}

void scope_check_ident(ident_t id);
{

}

void scope_check_number(number_t num);
{
    
}



