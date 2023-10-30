#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "symtab.h"
#include "utilities.h"

typedef struct
{
    const char *id;
    id_attrs *attrs;
} symtab_assoc_t;

// Invariant: 0 <= size < MAX_SCOPE_SIZE;
typedef struct scope_symtab_s
{
    unsigned int size;
    symtab_assoc_t *entries[MAX_SCOPE_SIZE];
} scope_symtab_t;

// The current scope (i.e., the symbol table)
// Idea: size is the index into entries
// of the most recent symtab_assoc added to the list of entries.
// So the next entry goes into the index size+1
static scope_symtab_t *symtab = NULL;

// Allocate a fresh scope symbol table and return (a pointer to) it.
// Issues an error message (on stderr) if there is no space
// and exits with a failure error code in that case.
static scope_symtab_t *symtab_create()
{
    scope_symtab_t *new_scope = (scope_symtab_t *)malloc(sizeof(scope_symtab_t));
    if (new_scope == NULL)
    {
        bail_with_error("No space for new scope_symtab_t!");
    }
    new_scope->size = 0;
    for (int j; j < MAX_SCOPE_SIZE; j++)
    {
        new_scope->entries[j] = NULL;
    }
    return new_scope;
}

// initialize the symbol table for the current scope
void symtab_initialize()
{
    // create the scope and assign it to the global symtab
    symtab = symtab_create();
}

// Return the current scope's next offset to use for allocation,
// which is the size of the current scope (number of declared ids).
unsigned int symtab_size()
{
    return symtab->size;
}

// Is the current scope full?
bool symtab_full()
{
    return symtab_size() >= MAX_SCOPE_SIZE;
}

// Requires: assoc != NULL && !symtab_full() && !symtab_declared(assoc->id);
// Add an association from the given name to the given id attributes
// in the current scope.
static void symtab_add(symtab_assoc_t *assoc)
{
    // assert(assoc != NULL);
    // assert(!symtab_full());
    // assert(!symtab_declared(assoc->id));
    symtab->entries[symtab->size] = assoc;
    symtab->size++;
}

// Requires: !symtab_declared(name) && attrs != NULL;
// Modify the current scope symbol table to
// add an association from the given name to the given id_attrs attrs.
void symtab_insert(const char *name, id_attrs *attrs)
{
    // assert(!symtab_declared(name));
    // assert(attrs != NULL);
    symtab_assoc_t *new_assoc = malloc(sizeof(symtab_assoc_t));
    if (new_assoc == NULL)
    {
        bail_with_error("No space for association!");
    }
    new_assoc->id = name;
    new_assoc->attrs = attrs;
    symtab_add(new_assoc);
}

// Requires: name != NULL;
// Is the given name associated with some attributes in the current scope?
bool symtba_declared(const char *name)
{
    // assert(symtab != NULL);
    // assert(name != NULL);
    return symtab_lookup(name) != NULL;
}

// Requires: name != NULL and symtab_initialize() has been called previously.
// Return (a pointer to) the attributes of the given name in the current scope
// or NULL if there is no association for name.
id_attrs *symtab_lookup(const char *name)
{
    int i;
    // assert(name != NULL);
    // assert(symtab != NULL);
    for (i = 0; i < symtab->size; i++)
    {
        // assert(symtab != NULL);
        // assert(symtab->entries != NULL);
        // assert(0 <= i && i < symtab->size);
        // assert(symtab->entries[i] != NULL);
        // assert(symtab->entries[i]->id != NULL);
        if (strcmp(symtab->entries[i]->id, name) == 0)
        {
            return symtab->entries[i]->attrs;
        }
    }
    // assert(i == symtab->size);
    return NULL;
}