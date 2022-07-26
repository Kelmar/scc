/* ===================================================================== */
/* ===================================================================== */

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "token.h"

/* ===================================================================== */

RET_NOTNULL
Token* new_token(char* lit, TokenType type, int lineNumber, const char* filename)
{
    Token* rval = (Token*)safe_alloc(sizeof(Token));

    rval->lit = lit;
    rval->type = type;
    rval->lineNumber = lineNumber;
    rval->filename = filename;

    return rval;
}

void delete_token(Token* t)
{
    if (!t)
        return;

    free(t->lit);
    free(t);
}

/* ===================================================================== */
