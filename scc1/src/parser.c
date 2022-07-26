#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "ast/node.h"

#include "parser.h"
#include "lexer.h"

typedef struct ParserTAG
{
	Lexer* lexer;  ///< The lexer this parser is reading from.
	int lastError; ///< The last error this parser encountered.
} Parser;

Parser* new_parser(Lexer* lexer)
{
	Parser* rval = (Parser*)malloc(sizeof(Parser));

	if (!rval)
		return NULL;

	memset(rval, 0, sizeof(Parser));

	rval->lexer = lexer;

	if (!lexer)
		rval->lastError = EINVAL;

	return rval;
}

void delete_parser(Parser* this)
{
	if (!this)
		return;

	delete_lexer(this->lexer);

	free(this);
}

int parser_lastError(Parser* this)
{
	return this->lastError;
}


AstNode* parser_parseFuncDecl(Parser* this)
{
	Token* t = lexer_getToken(this->lexer);

	if (!t)
		this->lastError = lexer_lastError(this->lexer);

	return NULL;
}
