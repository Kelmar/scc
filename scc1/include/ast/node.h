#pragma once

#include "comp.h"
#include "list.h"
#include "token.h"

typedef enum AstNodeTypeTAG
{
    ANT_FUNC_DECEL,
    ANT_RETURN_EXPR,
    ANT_INT_CONST,
    ANT_BASE_TYPE,
    ANT_USER_TYPE,
    ANT_ARG_DECL,
    ANT_ARG_LIST
} AstNodeType;

typedef struct AstNodeTAG AstNode;

typedef struct AstNodeTAG
{
    AstNodeType type;

    union
    {
        TokenType baseType;

        struct ArgDeclNodeTAG
        {
            TokenType baseType;
            char* argName; // TODO: Replace with entry in symtab
        } ArgDecl;

        List* argList;

        struct FuncDeclNodeTAG
        {
            AstNode* returnType;
            char* funcName; // TODO: Replace with entry in symtab
            List* argList;  // Argument list
        } FuncDecl;
    };
} AstNode;

RET_NOTNULL
AstNode* new_astNode(AstNodeType type);
void delete_astNode(AstNode*);
