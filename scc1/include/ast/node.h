#pragma once

typedef enum AstNodeTypeTAG
{
	ANT_FUNC_DECEL,
	ANT_RETURN_EXPR,
	ANT_INT_CONST,
} AstNodeType;

typedef struct AstNodeTAG
{
	AstNodeType type;
	void* data;
} AstNode;

