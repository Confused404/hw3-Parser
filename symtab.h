#ifndef _SYMTAB_H
#define _SYMTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "id_attrs.h"
#include "id_use.h"
#include "utilities.h"
#include "scope.h"
 
extern void symtab_initialize();

extern int size();

extern bool full();

extern bool declared(const char * name);

extern id_use * lookup(const char * name);

extern bool declared_in_current_scope(const char * name);

extern void insert(const char * name, id_attrs * attrs);

extern void symtab_enter_scope();

extern void symtab_leave_scope();

#endif