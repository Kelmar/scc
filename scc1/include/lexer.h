/* ===================================================================== */
/* ===================================================================== */

#pragma once

#include "comp.h"
#include "token.h"

/* ===================================================================== */

typedef struct LexerTAG Lexer;

RET_NOTNULL
Lexer* new_lexer(const char* filename);

void delete_lexer(Lexer*);

int lexer_lastError(const Lexer*);

Token* lexer_getToken(Lexer*);

/* ===================================================================== */
