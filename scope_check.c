#include "scope_check.h"

void scope_check_program(block_t prog)
{
    enter_scope();
    scope_check_block(prog);
    leave_scope();
}

void scope_check_block(block_t blk) // why is it extern in the unparser?
{
    scope_check_const_decls(blk.const_decls);
    scope_check_var_decls(blk.var_decls);
    scope_check_proc_decls(blk.proc_decls);
    scope_check_stmt(blk.stmt);
}

void scope_check_const_decls(const_decls_t cds)
{

}

void scope_check_const_decl(const_decl_t cd)
{

}

void scope_check_const_defs(const_defs_t cdfs)
{

}

void scope_check_const_def(const_def_t cdf)
{

}

void scope_check_var_decls(var_decls_t vds)
{
    var_decl_t *vdp = vds.var_decls;
    while (!ast_list_is_empty((void*)vdp)) //could be changed to vdp != NULL
    { 
	    scope_check_varDecl(*vdp);
	    vdp = vdp->next;
    }
}

void scope_check_var_decl(var_decl_t vd)
{
    scope_check_idents(vd.idents, vd.type_tag);
}

void scope_check_idents(idents_t idents, AST_type type_tag) //second parameter might be wrong
{
    ident_t *idp = idents.idents;
    while (!ast_list_is_empty((void*)idp)) //could be changed to idp != NULL
    { 
        scope_check_declare_ident(*idp);
        idp = idp->next;
    }
}

void scope_check_declare_ident(ident_t id) //might take a second parameter
{
    
}

void scope_check_proc_decls(proc_decls_t pds)
{

}

void scope_check_proc_decl(proc_decl_t pd)
{

}

void scope_check_stmts(stmts_t stmts)
{
    
}

void scope_check_stmt(stmt_t stmt)
{
    switch(stmt.stmt_kind) 
    {
        case assign_stmt:
            scope_check_assign_stmt(stmt.data.assign_stmt);
            break;
        case call_stmt:
            scope_check_call_stmt(stmt.data.call_stmt);
            break;
        case begin_stmt:
            scope_check_begin_stmt(stmt.data.begin_stmt);
            break;
        case if_stmt:
            scope_check_if_stmt(stmt.data.if_stmt);
            break;
        case while_stmt: 
            scope_check_while_stmt(stmt.data.while_stmt);
            break;
        case read_stmt:
            scope_check_read_stmt(stmt.data.read_stmt);
            break;
        case write_stmt:
            scope_check_write_stmt(stmt.data.write_stmt);
            break;
        case skip_stmt:
            scope_check_skip_stmt(); //need to add parameter
            break;
        default:
            bail_with_error("Call to scope_check_stmt with an AST that is not a statement!");
	        break;
    }
}

void scope_check_assign_stmt(assign_stmt_t stmt)
{
    const char *name = stmt.name;
    id_use *idu = scope_check_ident_declared(*(stmt.file_loc), name);
    assert(idu != NULL);
    scope_check_expr(*(stmt.expr));
}

void scope_check_call_stmt(call_stmt_t stmt)
{

}

void scope_check_begin_stmt(begin_stmt_t stmt)
{
    symtab_enter_scope();
    scope_check_stmts(stmt.stmts);
    symtab_leave_scope();
}

void scope_check_if_stmt(if_stmt_t stmt)
{
    scope_check_condition(stmt.condition);
    scope_check_stmt(*(stmt.then_stmt));
    scope_check_stmt(*(stmt.else_stmt));
}

void scope_check_while_stmt(while_stmt_t stmt)
{

}

void scope_check_read_stmt(read_stmt_t stmt)
{
     scope_check_ident_declared(*(stmt.file_loc), stmt.name);
}

void scope_check_write_stmt(write_stmt_t stmt)
{
    scope_check_expr(stmt.expr);
}

void scope_check_skip_stmt(int level)
{

}

void scope_check_condition(condition_t cond)
{

}

void scope_check_odd_condition(odd_condition_t cond)
{

}

void scope_check_rel_op_condition(rel_op_condition_t cond)
{

}

void scope_check_token(token_t token)
{

}

void scope_check_expr(expr_t exp)
{
    switch (exp.expr_kind)
    {
        case expr_bin:
            scope_check_bin_op_expr(exp.data.binary);
            break;
        case expr_ident:
            scope_check_ident_expr(exp.data.ident);
            break;
        case expr_number:
            // no identifiers are possible in this case, so just return
            break;
        default: 
            bail_with_error("Unexpected expr_kind_e (%d) in scope_check_expr", exp.expr_kind);
            break;
    }
}

void scope_check_bin_op_expr(binary_op_expr_t exp)
{
    scope_check_expr(*(exp.expr1));
    // (note: no identifiers can occur in the operator)
    scope_check_expr(*(exp.expr2));
}

void scope_check_ident_expr(ident_t id)
{
    scope_check_ident_declared(*(id.file_loc), id.name);
}

id_use *scope_check_ident_declared(file_location floc, const char *name)
{
    id_use *ret = symtab_lookup(name);
    if (ret == NULL) {
	bail_with_prog_error(floc, "identifier \"%s\" is not declared!", name);
    }
    return ret;
}

void scope_check_number(number_t num)
{

}



