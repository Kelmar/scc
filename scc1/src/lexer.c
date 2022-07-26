/* ===================================================================== */
/* ===================================================================== */

#include "cbool.h"

#include "error.h"
#include "token.h"
#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===================================================================== */

typedef struct LexerTAG
{
    FILE* file;         ///< The open file handle for this lexer
    int   lastError;    ///< The last error encountered
    char  buffer[1024]; ///< Current line buffer
    int   index;        ///< Current index into the line buffer

    // These two can be adjusted with the #line directive
    char* filename;     ///< Name of the current file we're parsing
    int   lineNumber;   ///< The current line number we're parsing
} Lexer;

/* ===================================================================== */

typedef struct KeywordTAG
{
    const char* keyword;
    TokenType type;
} Keyword;

Keyword g_keywords_0[] =
{
    { 0, 0 }
};

Keyword g_keywords_1[] =
{
    { 0, 0 }
};

Keyword g_keywords_2[] =
{
    { "do", KW_DO },
    { "if", KW_IF },

    { 0, 0 }
};

Keyword g_keywords_3[] =
{
    { "for", KW_FOR },
    { "int", KW_INT },

    { 0, 0 }
};

Keyword g_keywords_4[] =
{
    { "auto", KW_AUTO },
    { "case", KW_CASE },
    { "char", KW_CHAR },
    { "else", KW_ELSE },
    { "enum", KW_ENUM },
    { "goto", KW_GOTO },
    { "long", KW_LONG },
    { "void", KW_VOID },

    { 0, 0 }
};

Keyword g_keywords_5[] =
{
    { "break", KW_BREAK },
    { "const", KW_CONST },
    { "float", KW_FLOAT },
    { "short", KW_SHORT },
    { "union", KW_UNION },
    { "while", KW_WHILE },

    { 0, 0 }
};

Keyword g_keywords_6[] =
{
    { "double", KW_DOUBLE },
    { "extern", KW_EXTERN },
    { "return", KW_RETURN },
    { "sizeof", KW_SIZEOF },
    { "static", KW_STATIC },
    { "struct", KW_STRUCT },
    { "switch", KW_SWITCH },

    { "_int_8", KW__INT_8 },

    { 0, 0 }
};

Keyword g_keywords_7[] =
{
    { "default", KW_DEFAULT },
    { "typedef", KW_TYPEDEF },

    { "_int_16", KW__INT_16 },
    { "_int_32", KW__INT_32 },
    { "_int_64", KW__INT_64 },

    { 0, 0 }
};

Keyword g_keywords_8[] =
{
    { "continue", KW_CONTINUE },
    { "register", KW_REGISTER },
    { "unsigned", KW_UNSIGNED },
    { "volatile", KW_VOLATILE },

    { 0, 0 }
};

Keyword* g_keywords[] =
{
    g_keywords_0, g_keywords_1, g_keywords_2, g_keywords_3, g_keywords_4, g_keywords_5, g_keywords_6, g_keywords_7, g_keywords_8
};

const int MAX_KEYWORDS = (sizeof(g_keywords) / sizeof(void*));

/* ===================================================================== */

RET_NOTNULL
Lexer* new_lexer(const char* filename)
{
    Lexer* rval = (Lexer*)safe_alloc(sizeof(Lexer));

    rval->file = fopen(filename, "r");

    if (!rval->file)
    {
        char* errStr = strerror(errno);
        fatal(NULL, ERR_CantOpenFile, "Can't open file '%s': %s", filename, errStr);
    }
    else
        rval->filename = safe_dup(filename);

    return rval;
}

void delete_lexer(Lexer* this)
{
    if (!this)
        return;

    free(this->filename);

    fclose(this->file);

    free(this);
}

/* ===================================================================== */

int lexer_lastError(const Lexer* this)
{ 
    if (this)
        return this->lastError;

    return EINVAL;
}

/* ===================================================================== */

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

/* ===================================================================== */

Token* lexer_parseNumber(Lexer* this)
{
    int start = this->index;

    while (isdigit(this->buffer[this->index]))
        ++this->index;

    char* lit = safe_slice(this->buffer + start, this->index - start);

    return new_token(lit, TOK_ConstInt, this->lineNumber, this->filename);
}

/* ===================================================================== */

Token* lexer_parseWord(Lexer* this)
{
    int start = this->index;

    for (;;)
    {
        char c = this->buffer[this->index];

        if (!isalnum(c) && c != '_')
            break;

        ++this->index;
    }

    int len = this->index - start;
    TokenType type = TOK_Identifier;

    char* lit = safe_slice(this->buffer + start, len);

    if (len < MAX_KEYWORDS)
    {
        for (int i = 0; g_keywords[len][i].keyword; ++i)
        {
            if (strncmp(g_keywords[len][i].keyword, lit, len) == 0)
            {
                type = g_keywords[len][i].type;
                break;
            }
        }
    }

    return new_token(lit, type, this->lineNumber, this->filename);
}

/* ===================================================================== */

Token* lexer_parseSymbol(Lexer* this)
{
    char c = this->buffer[this->index++];
    char* lit = safe_slice(this->buffer + this->index - 1, 1);

    return new_token(lit, c, this->lineNumber, this->filename);
}

/* ===================================================================== */

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
        else if (isalpha(c) || c == '_')
            return lexer_parseWord(this);
        else
            return lexer_parseSymbol(this);
    }
}

/* ===================================================================== */
