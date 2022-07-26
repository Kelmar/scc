#pragma once

#include "lexer.h"

typedef struct ParserTAG Parser;

Parser* new_parser(Lexer*);
void delete_parser(Parser*);

int parser_lastError(Parser*);

