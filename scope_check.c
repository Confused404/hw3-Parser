#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scope_check.h"
#include "id_attrs.h"
#include "file_location.h"
#include "ast.h"
#include "utilities.h"
#include "symtab.h"
#include "scope_check.h"

// Build the symbol table for the given program AST
// and Check the given program AST for duplicate declarations
// or uses of identifiers that were not declared
void scope_check_program(AST *prog)
{
    symtab_enter_scope(); // // //we are missing a definition for this function
    scope_check_varDecls(prog->data.program.vds);
    scope_check_stmt(prog->data.program.stmt);
    symtab_leave_scope(); // // //we are missing a definition for this function
}

// build the symbol table and check the declarations in vds
void scope_check_varDecls(AST_list vds)
{
    while (!ast_list_is_empty(vds)) {
	scope_check_varDecl(ast_list_first(vds)); // // // ast_list_first is not defined
	vds = ast_list_rest(vds);                 // // // ast_list_rest is not defined
    }
}

// check the var declaration vd
// and add it to the current scope's symbol table
// or produce an error if the name has already been declared
void scope_check_varDecl(AST *vd)
{
    int ofst = symtab_next_loc_offset(); // // // symtab_next_loc_offset is not defined
    id_attrs *attrs = id_attrs_loc_create(vd->file_loc, vd->data.var_decl.vt, ofst); // // // id_attrs_loc_create is not defined
    const char *name = vd->data.var_decl.name;
    symtab_insert(name, attrs);
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_stmt(AST *stmt)
{
    switch (stmt->type_tag) {
    case assign_ast:
	scope_check_assignStmt(stmt);
	break;
    case begin_ast:
	scope_check_beginStmt(stmt);
	break;
    case if_ast:
	scope_check_ifStmt(stmt);
	break;
    case read_ast:
	scope_check_readStmt(stmt);
	break;
    case write_ast:
	scope_check_writeStmt(stmt);
	break;
    default:
	bail_with_error("Call to scope_check_stmt with an AST that is not a statement!");
	break;
    }
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_assignStmt(AST *stmt)
{
    const char *name = stmt->data.assign_stmt.ident->data.ident.name;
    id_use *idu = scope_check_ident_is_data(stmt->file_loc, name);
    stmt->data.assign_stmt.ident->data.ident.idu = idu;
    scope_check_expr(stmt->data.assign_stmt.exp);
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_beginStmt(AST *stmt)
{
    symtab_enter_scope(); // // // symtab_enter_scope is not defined
    scope_check_varDecls(stmt->data.begin_stmt.vds);
    AST_list stmts = stmt->data.begin_stmt.stmts;
    while (!ast_list_is_empty(stmts)) {
	scope_check_stmt(ast_list_first(stmts)); // // // ast_list_first is not defined
	stmts = ast_list_rest(stmts);            // // // ast_list_rest is not defined
    }
    symtab_leave_scope();                    // // // symtab_leave_scope is not defined
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_ifStmt(AST *stmt)
{
    scope_check_expr(stmt->data.if_stmt.exp);
    scope_check_stmt(stmt->data.if_stmt.stmt);
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_readStmt(AST *stmt)
{
    stmt->data.read_stmt.ident->data.ident.idu
	= scope_check_ident_is_data(stmt->file_loc,
				    stmt->data.read_stmt.ident->data.ident.name);
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_writeStmt(AST *stmt)
{
    scope_check_expr(stmt->data.write_stmt.exp);
}

// check the expresion to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_expr(AST *exp)
{
    switch (exp->type_tag) {
    case ident_ast:
	{   // must update the id_use in the AST
	    id_use *idu
		= scope_check_ident_is_data(exp->file_loc,
					    exp->data.ident.name);
	    exp->data.ident.idu = idu;
	}
	break;
    case bin_expr_ast:
	scope_check_bin_expr(exp);
	break;
    case number_ast:
	// no identifiers are possible in this case, so just return
	break;
    case not_expr_ast:
	scope_check_expr(exp->data.not_expr.exp);
	break;
    default:
	bail_with_error("Unexpected type_tag (%d) in scope_check_expr (for line %d, column %d)!",
			exp->type_tag, exp->file_loc.line, exp->file_loc.column);
	break;
    }
}

// check the expression (exp) to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_bin_expr(AST *exp)
{
    scope_check_expr(exp->data.bin_expr.leftexp);
    scope_check_expr(exp->data.bin_expr.rightexp);
}

// check that the given name has been declared,
// if so, then return an id_use (containing the attributes) for that name,
// otherwise, produce an error using the file_location (floc) given.
static id_use *scope_check_ident_declared(file_location floc, const char *name)
{
    id_use *ret = symtab_lookup(name);
    if (ret == NULL) {
	general_error(floc, "identifier \"%s\" is not declared!", name); // // // general_error is not defined
    }
    return ret;
}

// check that the given constant or variable name has been declared,
// if so, then return an id_use (containing the attributes) for that name,
// otherwise, produce an error using the file_location (floc) given.
id_use *scope_check_ident_is_data(file_location floc, const char *name)
{
    return scope_check_ident_declared(floc, name);
}