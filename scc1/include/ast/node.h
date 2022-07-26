#pragma once

#include "comp.h"
#include "token.h"

typedef enum AstNodeTypeTAG
{
	ANT_FUNC_DECEL,
	ANT_RETURN_EXPR,
	ANT_INT_CONST,
	ANT_BASE_TYPE,
	ANT_USER_TYPE
} AstNodeType;

typedef struct AstNodeTAG
{
	AstNodeType type;

	union
	{
	    void* data;

	    struct BaseTypeNodeTAG
	    {
		    TokenType baseType;
	    };

	    /*
	    struct UserTypeNodeTAG
	    {
	    };
	    */
	};
} AstNode;

RET_NOTNULL
AstNode* new_astNode(AstNodeType type);
void delete_astNode(AstNode*);
