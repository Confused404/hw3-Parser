#ifndef _SYMTAB_H
#define _SYMTAB_H

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "scope_check.h"
#include "utilities.h"
#include "unparser.h"
#include "id_attrs.h"
#include "id_use.h"

#define MAX_SCOPE_SIZE 4096

extern void initialize();

extern int size();

extern bool full();

extern bool declared(char * name);

extern id_use *lookup(char * name);

extern bool declared_in_current_scope(char * name);

extern void insert( char * name, id_attrs *attrs);

extern void enter_scope();

extern void leave_scope();

#endif
