/* ===================================================================== */
/* ===================================================================== */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "ast/node.h"

#include "error.h"
#include "parser.h"
#include "lexer.h"

/* ===================================================================== */

typedef struct ParserTAG
{
    Lexer* lexer;  ///< The lexer this parser is reading from.
    int lastError; ///< The last error this parser encountered.
} Parser;

/* ===================================================================== */

RET_NOTNULL
Parser* new_parser(Lexer* lexer)
{
    if (!lexer)
	fatal(NULL, ERR_InternalError, "Invalid lexer pointer");

    Parser* rval = (Parser*)safe_alloc(sizeof(Parser));
    rval->lexer = lexer;
    return rval;
}

void delete_parser(Parser* this)
{
    if (!this)
	return;

    delete_lexer(this->lexer);

    free(this);
}

/* ===================================================================== */

int parser_lastError(Parser* this)
{
    return this->lastError;
}

/* ===================================================================== */
/*
 * type: 'int'
 *     | 'char'
 *     | 'long'
 *     | 'void'
 *     | 'float'
 *     | 'short'
 *     | 'double'
 *     // Nonstandard
 *     | '_int_8'
 *     | '_int_16'
 *     | '_int_32'
 *     | '_int_64'
 *     ;
 */
AstNode* parser_parseType(Parser* this)
{
    Token* t = lexer_getToken(this->lexer);

    if (!t)
    {
	this->lastError = lexer_lastError(this->lexer);
	return NULL;
    }

    AstNode* rval = NULL;

    // We're expecting a type
    switch (t->type)
    {
    case KW_INT:
    case KW_CHAR:
    case KW_LONG:
    case KW_VOID:
    case KW_FLOAT:
    case KW_SHORT:
    case KW_DOUBLE:
    case KW__INT_8:
    case KW__INT_16:
    case KW__INT_32:
    case KW__INT_64:
	rval = new_astNode(ANT_BASE_TYPE);
	break;

    default:
	error(t, ERR_UnknownType, "Unknown type: '%s'", t->lit);
	this->lastError = ERR_UnknownType;
	break;
    }

    return rval;
}

/* ===================================================================== */
/*
 * argument_decl: type
 *              | type identifire
 *              ;
 */
AstNode* parser_parseArgumentDecl(Parser* this)
{
    return NULL;
}

/* ===================================================================== */
/*
 * argument_list:
 *              | argument_decl ',' argument_list
 *              | argument_decl
 *              ;
 */
AstNode* parser_parseArgumentList(Parser* this)
{
    return NULL;
}

/* ===================================================================== */
/*
 * func_proto: type identifier '(' argument_list ')'
 */
AstNode* parser_parseFuncProto(Parser* this)
{
    // First expect a type.

    return NULL;
}

/* ===================================================================== */

AstNode* parser_getTree(Parser* this)
{
    // For now all we can do is a function declaration.
    return parser_parseFuncProto(this);
}

/* ===================================================================== */
