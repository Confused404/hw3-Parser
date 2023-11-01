#include "symtab.h"

typedef struct
{
    const char *id;
    id_attrs *attrs;
} symtab_assoc_t;

typedef struct scope_symtab_s
{
    unsigned int size;
    symtab_assoc_t *entries[MAX_SCOPE_SIZE];
} scope_symtab_t;

static scope_symtab_t *symtab = NULL;

void symtab_initialize()
{
    symtab = (scope_symtab_t *)malloc(sizeof(scope_symtab_t));
    if(symtab == NULL)
    {
        bail_with_error("No space for symbol table!");
    }
    symtab->size = 0;
    for(int i = 0; i < MAX_SCOPE_SIZE; i++)
    {
        symtab->entries[i] = NULL;
    }
}

int size()
{
    return symtab->size;
}

bool full()
{
    return size() >= MAX_SCOPE_SIZE;
}

bool declared(const char * name)
{
    if(lookup(name) == NULL)
    {
        return false;
    }
    return true;
}

id_attrs lookup(const char * name)
{
    for(int i = 0; i < size(); i++)
    {
        if(strcmp(symtab->entries[i]->id, name) == 0)
        {
            return &symtab->entries[i]->attrs;
        }
    }
    return NULL;
}

bool declared_in_current_scope(const char * name)
{

}

void insert(const char * name, id_attrs * attrs)
{

}

void enter_scope()
{

}

void leave_scope()
{

}

