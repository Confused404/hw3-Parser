#ifndef _SCOPE_CHECK_H
#define _SCOPE_CHECK_H

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include "symtab.h"
#include "utilities.h"
#include "unparser.h"
#include "id_attrs.h"
#include "id_use.h"

void scope_check_program(block_t);

#endif