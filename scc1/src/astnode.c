/* ===================================================================== */
/* ===================================================================== */

#include <stdlib.h>
#include <string.h>

#include "ast/node.h"

#include "error.h"

/* ===================================================================== */

RET_NOTNULL
AstNode* new_astNode(AstNodeType type)
{
    AstNode* rval = (AstNode*)safe_alloc(sizeof(AstNode));
    rval->type = type;

    return rval;
}

void delete_astNode(AstNode* this)
{
    if (!this)
        return;

    free(this);
}

/* ===================================================================== */
