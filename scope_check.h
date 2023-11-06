#ifndef _SCOPE_CHECK_H
#define _SCOPE_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "symtab.h"
#include "id_attrs.h"
#include "id_use.h"
#include "utilities.h"

extern void scope_check_program(block_t prog);

extern void scope_check_block(block_t blk);

extern void scope_check_const_decls(const_decls_t cds);

extern void scope_check_const_decl(const_decl_t cd);

extern void scope_check_const_defs(const_defs_t cdfs);

extern void scope_check_const_def(const_def_t cdf);

extern void scope_check_var_decls(var_decls_t vds);

extern void scope_check_var_decl(var_decl_t vd);

extern void scope_check_idents(idents_t idents);

extern void scope_check_declare_ident(ident_t id);

extern void scope_check_proc_decls(proc_decls_t pds);

extern void scope_check_proc_decl(proc_decl_t pd);

extern void scope_check_stmts(stmts_t stmts);

extern void scope_check_stmt(stmt_t stmt);

extern void scope_check_assign_stmt(assign_stmt_t stmt);

extern void scope_check_call_stmt(call_stmt_t stmt);

extern void scope_check_begin_stmt(begin_stmt_t stmt);

extern void scope_check_if_stmt(if_stmt_t stmt);

extern void scope_check_while_stmt(while_stmt_t stmt);

extern void scope_check_read_stmt(read_stmt_t stmt);

extern void scope_check_write_stmt(write_stmt_t stmt);

extern void scope_check_condition(condition_t cond);

extern void scope_check_odd_condition(odd_condition_t cond);

extern void scope_check_rel_op_condition(rel_op_condition_t cond);

extern void scope_check_token(token_t token);

extern void scope_check_expr(expr_t exp);

extern void scope_check_bin_op_expr(binary_op_expr_t exp);

extern void scope_check_ident_expr(ident_t id);

extern void scope_check_ident_declared(file_location floc, const char *name);

#endif