#include "cbool.h"

#include "token.h"
#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LexerTAG
{
    FILE* file;         ///< The open file handle for this lexer
    int   lastError;    ///< The last error encountered
    char  buffer[1024]; ///< Current line buffer
    int   index;        ///< Current index into the line buffer
    int   lineNumber;   ///< The current line number we're parsing
} Lexer;

Lexer* new_lexer(const char* filename)
{
    Lexer* rval = (Lexer*)malloc(sizeof(Lexer));

    if (!rval)
        return NULL;

    memset(rval, 0, sizeof(Lexer));

    rval->file = fopen(filename, "r");

    if (!rval->file)
        rval->lastError = errno;

    return rval;
}

void delete_lexer(Lexer* this)
{
    if (!this)
        return;

    fclose(this->file);

    free(this);
}

int lexer_lastError(const Lexer* this)
{ 
    if (this)
        return this->lastError;

    return EINVAL;
}

bool lexer_getLine(Lexer* this)
{
    if (this->buffer[this->index])
        return true;

    char *res = fgets(this->buffer, sizeof(this->buffer), this->file);

    if (!res)
    {
        this->lastError = errno;
        return false;
    }

    this->index = 0;
    this->lineNumber++;

    return true;
}

Token* lexer_parseNumber(Lexer* this)
{
    int start = this->index;

    while (isdigit(this->buffer[this->index]))
        ++this->index;

    return new_token(this->buffer + start, this->index - start, CONST_INT, this->lineNumber);
}

Token* lexer_parseWord(Lexer* this)
{
    int start = this->index;

    while (isalnum(this->buffer[this->index]))
        ++this->index;

    return new_token(this->buffer + start, this->index - start, IDENTIFIER, this->lineNumber);
}

Token* lexer_parseSymbol(Lexer* this)
{
    char c = this->buffer[this->index++];
    char lit[2] = { c, 0 };

    return new_token(lit, 1, c, this->lineNumber);
}

Token* lexer_getToken(Lexer* this)
{
    if (this->lastError)
        return NULL;

    for (;;)
    {
        if (!lexer_getLine(this))
            return NULL; // Errored

        char c = this->buffer[this->index];

        if (isspace(c))
        {
            // Ignore white space
            ++this->index;
            continue;
        }

        if (isdigit(c))
            return lexer_parseNumber(this);
        else if (isalpha(c))
            return lexer_parseWord(this);
        else
            return lexer_parseSymbol(this);
    }
}
