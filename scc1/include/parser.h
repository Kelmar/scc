/* ===================================================================== */
/* ===================================================================== */

#pragma once

#include "ast/node.h"

#include "error.h"
#include "lexer.h"

/* ===================================================================== */

typedef struct ParserTAG Parser;

RET_NOTNULL
Parser* new_parser(Lexer*);
void delete_parser(Parser*);

int parser_lastError(Parser*);

AstNode* parser_getTree(Parser*);

/* ===================================================================== */
