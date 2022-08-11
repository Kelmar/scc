/* ===================================================================== */
/* ===================================================================== */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "ast/node.h"

#include "cbool.h"
#include "error.h"
#include "strobj.h"
#include "parser.h"
#include "lexer.h"

/* ===================================================================== */

typedef struct ParserTAG
{
    Lexer* lexer;        ///< The lexer this parser is reading from.
    int lastError;       ///< The last error this parser encountered.

    Token* currentToken; ///< The current token we're looking at.
    Token* nextToken;    ///< Look ahead token for parsing.
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

void parser_getNextToken(Parser* this)
{
    if (!this->nextToken)
	this->nextToken = lexer_getToken(this->lexer);

    if (this->currentToken)
    {
	if (this->currentToken->type == TOK_EndOfFile)
	    return; // Don't move forward from EOF

	delete_token(this->currentToken);
    }

    this->currentToken = this->nextToken;
    this->nextToken = lexer_getToken(this->lexer);
}

/* ===================================================================== */
/*
 * Used for error recovery.
 * 
 * Consumes tokens until we reach the EOF or the supplied token type.
 */ 
void parser_recoverTo(Parser* this, TokenType type)
{
    while (this->currentToken && this->currentToken->type != TOK_EndOfFile && this->currentToken->type != type)
	parser_getNextToken(this);
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
AstNode* parser_parseType(Parser* this, TokenType recoverTok)
{
    AstNode* rval = NULL;

    // We're expecting a type
    switch (this->currentToken->type)
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
	rval->baseType = this->currentToken->type;
	break;

    default:
	error(this->currentToken, ERR_UnexpectedToken, "Unexpected token '%s', expected type", this->currentToken->lit);
	parser_recoverTo(this, recoverTok);
	break;
    }

    parser_getNextToken(this);

    return rval;
}

/* ===================================================================== */
/*
 * argument_decl: type
 *              | type identifier
 *              ;
 */
AstNode* parser_parseArgumentDecl(Parser* this)
{
    AstNode* type = parser_parseType(this, ',');

    if (!type)
	return NULL;

    AstNode* rval = new_astNode(ANT_ARG_DECL);
    rval->ArgDecl.baseType = type->baseType;
    rval->ArgDecl.argName = NULL;

    if (this->currentToken && this->currentToken->type == TOK_Identifier)
    {
	// TODO: Add entry into symbol table here.

	rval->ArgDecl.argName = new_stringCopy(this->currentToken->lit);

	delete_astNode(type);
	parser_getNextToken(this);
    }

    return rval;
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
    AstNode* rval = new_astNode(ANT_ARG_LIST);

    bool first = true;

    for (;;)
    {
	AstNode* arg = parser_parseArgumentDecl(this);

	if (!arg)
	{
	    if (first)
		break; // Empty argument list is okay

	    error(this->currentToken, ERR_UnexpectedToken, "Unexpected token '%s', expected type", this->currentToken->lit);
	    delete_astNode(rval);
	    parser_recoverTo(this, ')');
	    return NULL;
	}

	first = false;

	list_insert(rval->argList, arg);

	if (this->currentToken->type != ',')
	    break;

	parser_getNextToken(this); // Consume comma and continue
    }

    return rval;
}

/* ===================================================================== */
/*
 * func_proto: type identifier '(' argument_list ')'
 */
AstNode* parser_parseFuncProto(Parser* this)
{
    AstNode* returnType = parser_parseType(this, '(');
    
    if (!returnType)
	return NULL;

    if (this->currentToken->type != TOK_Identifier)
    {
	error(this->currentToken, ERR_UnexpectedToken, "Expected identifier");
	delete_astNode(returnType);
	parser_recoverTo(this, ';');
	return NULL;
    }

    // TODO: Insert the identifier into the symtab here.
    String* name = new_stringCopy(this->currentToken->lit);

    parser_getNextToken(this);

    if (this->currentToken->type != '(')
    {
	error(this->currentToken, ERR_UnexpectedToken, "Unexpected token '%s', expected (", this->currentToken->lit);
	delete_astNode(returnType);
	delete_string(name);
	parser_recoverTo(this, ')');
	return NULL;
    }

    parser_getNextToken(this);
    AstNode* argList = parser_parseArgumentList(this);

    if (this->currentToken->type != ')')
    {
	error(this->currentToken, ERR_UnexpectedToken, "Unexpected token '%s', expected )", this->currentToken->lit);

	delete_string(name);
	delete_astNode(returnType);
	delete_astNode(argList);

	parser_recoverTo(this, ';');

	return NULL;
    }

    AstNode* rval = new_astNode(ANT_FUNC_DECEL);

    rval->FuncDecl.argList = argList->argList;
    rval->FuncDecl.returnType = returnType;
    rval->FuncDecl.funcName = name;

    return rval;
}

/* ===================================================================== */

AstNode* parser_getTree(Parser* this)
{
    // For now all we can do is a function declaration.

    if (!this->currentToken)
	parser_getNextToken(this);

    return parser_parseFuncProto(this);
}

/* ===================================================================== */
