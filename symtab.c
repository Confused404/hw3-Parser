// test
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "scope_check.h"
#include "utilities.h"
#include "unparser.h"

void initialize();


int size();


bool full();



bool declared(name);



id_use *lookup(name);



bool declared_in_current_scope(name);



void insert(name, id_attrs);


void enter_scope();


void leave_scope();