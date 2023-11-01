#include "symtab.h"

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

static scope_symtab_t *symtab = NULL;

void symtab_initialize()
{
    symtab = (scope_symtab_t *)malloc(sizeof(scope_symtab_t));
    if(symtab == NULL)
    {
        bail_with_error("No space for symbol table!");
    }
    symtab->size = 0;
    symtab->current_scope = 0;
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

id_use * lookup(const char * name)
{
    for(int i = 0; i < size(); i++)
    {
        if(strcmp(symtab->entries[i]->id, name) == 0)
        {
            return id_use_create(symtab->entries[i]->attrs, i);
        }
    }
    return NULL;
}

bool declared_in_current_scope(const char * name)
{
    if(declared(name) && lookup(name)->levelsOutward == symtab->current_scope) // to check if declared and in current scope
    {
        return true;
    }
    return false;
}

void insert(const char * name, id_attrs * attrs)
{
    symtab_assoc_t *new_assoc = malloc(sizeof(symtab_assoc_t));
    if (new_assoc == NULL)
    {
        bail_with_error("No space for association!");
    }
    new_assoc->id = name;
    new_assoc->attrs = attrs;
    symtab->entries[symtab->size] = new_assoc;
    symtab->size++;
}

void enter_scope()
{
    symtab->current_scope++;
}

void leave_scope()
{
    while(size() > 0 && lookup(symtab->entries[size() - 1]->id)->levelsOutward == symtab->current_scope)
    {
        symtab->size--;
    }
    symtab->current_scope--;
}

