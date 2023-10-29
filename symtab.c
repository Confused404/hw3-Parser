#include "symtab.h"

void initialize();

int size();

bool full();

bool declared(char * name);

id_use *lookup(char * name);

bool declared_in_current_scope(char * name);

void insert(char * name, id_attrs *attrs);

void enter_scope();

void leave_scope();