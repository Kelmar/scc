#pragma once

#include "token.h"

typedef struct LexerTAG Lexer;

Lexer* new_lexer(const char* filename);
void delete_lexer(Lexer*);

int lexer_lastError(Lexer*);

Token* lexer_getToken(Lexer*);
