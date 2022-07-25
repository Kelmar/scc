#include <stdlib.h>
#include <string.h>

#include "token.h"

Token* new_token(const char* lit, int litLen, TokenType type, int lineNumber)
{
    Token* rval = (Token*)malloc(sizeof(Token));

    if (!rval)
        return NULL;

    memset(rval, 0, sizeof(Token));

    rval->lit = malloc(litLen + 1);
    rval->type = type;
    rval->lineNumber = lineNumber;

    if (!rval->lit)
    {
        free(rval);
        return NULL;
    }

    memset(rval->lit, 0, litLen + 1);
    strncpy(rval->lit, lit, litLen);

    return rval;
}

void delete_token(Token* t)
{
    if (!t)
        return;

    free(t->lit);
    free(t);
}
