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
 
#define MAX_SCOPE_SIZE 4096

typedef struct 
{
    const char *id;
    id_attrs *attrs;
} symtab_assoc_t;

typedef struct scope_symtab_s
{
    unsigned int size;
    unsigned int current_scope;
    symtab_assoc_t *entries[MAX_SCOPE_SIZE];
} scope_symtab_t;

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