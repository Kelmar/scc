/* ===================================================================== */
/* ===================================================================== */

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "token.h"
#include "strobj.h"

/* ===================================================================== */

RET_NOTNULL
Token* new_token(String* lit, TokenType type, int lineNumber, const String* filename)
{
    Token* rval = (Token*)safe_alloc(sizeof(Token));

    rval->lit = new_stringCopy(lit);
    rval->type = type;
    rval->lineNumber = lineNumber;
    rval->filename = filename;

    return rval;
}

void delete_token(Token* t)
{
    if (!t)
        return;

    delete_string(t->lit);
    free(t);
}

/* ===================================================================== */
