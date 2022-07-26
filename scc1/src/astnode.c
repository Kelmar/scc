/* ===================================================================== */
/* ===================================================================== */

#include <stdlib.h>
#include <string.h>

#include "ast/node.h"

#include "error.h"
#include "list.h"

/* ===================================================================== */

RET_NOTNULL
AstNode* new_astNode(AstNodeType type)
{
    AstNode* rval = (AstNode*)safe_alloc(sizeof(AstNode));
    rval->type = type;

    switch (rval->type)
    {
    case ANT_ARG_LIST:
        rval->argList = new_list();
        break;
    }

    return rval;
}

void delete_astNode(AstNode* this)
{
    if (!this)
        return;

    switch (this->type)
    {
    case ANT_ARG_DECL:
        free(this->ArgDecl.argName);
        break;

    case ANT_ARG_LIST:
        delete_list(this->argList, delete_astNode);
        break;
    }

    free(this);
}

/* ===================================================================== */
