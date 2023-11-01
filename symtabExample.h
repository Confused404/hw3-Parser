// EXAMPLE CODE

#ifndef _SYMTAB_H

#define _SYMTAB_H

#include <stdbool.h>
#include "ast.h"
#include "id_attrs.h"

// Maximum number of declarations that can be stored in a scope
#define MAX_SCOPE_SIZE 4096

// initialize the symbol table for the current scope
extern void symtab_initialize();

// Return the current scope's next offset to use for allocation,
// which is the size of the current scope (number of declared ids).
extern unsigned int symtab_size();

// Is the current scope full?
extern bool symtab_full();

// Is the given name associated with some attributes in the current scope?
extern bool symtab_declared(const char *name);

// Requires: !symtab_declared(name) && attrs != NULL;
// Modify the current scope symbol table to
// add an association from the given name to the given id_attrs attrs.
extern void symtab_insert(const char *name, id_attrs *attrs);

// Return (a pointer to) the attributes of the given name in the current scope
// or NULL if there is no association for name.
extern id_attrs *symtab_lookup(const char *name);

#endif