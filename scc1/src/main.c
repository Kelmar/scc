/* ===================================================================== */
/* ===================================================================== */

#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "parser.h"

/* ===================================================================== */

/*
 * Stage 1 compiling.
 * 
 * This occurs after the preprocessor has done it's thing.
 * 
 * We need to keep an eye out for "#line" directives while lexing; that will
 * change the file name and line number, which we'll need for error reporting.
 */

 /* ===================================================================== */

char g_filename[1024] = { 0 };

/* ===================================================================== */

void parseArgs(int argc, const char** argv)
{
    // Really terrible parameter parsing for now.

    for (int i = 1; i < argc; ++i)
    {
        if (i == 1)
            strncpy(g_filename, argv[1], sizeof(g_filename));
    }
}

/* ===================================================================== */

void mainLoop(Lexer* l, Parser* p)
{
    AstNode* ast = parser_getTree(p);

    delete_parser(p);

    //for (;;)
    //{
    //    Token* t = lexer_getToken(l);

    //    if (!t)
    //        break;

    //    printf("0x%08X TOKEN: %s\r\n", t->type, t->lit);

    //    delete_token(t);
    //}

    //delete_lexer(l);
}

/* ===================================================================== */

int main(int argc, const char** argv)
{
    parseArgs(argc, argv);

    if (!g_filename[0])
    {
        fprintf(stderr, "No filename supplied.\r\n");
        return 1;
    }

    Lexer* l = new_lexer(g_filename);
    Parser* p = new_parser(l);

    mainLoop(l, p);

    return 0;
}

/* ===================================================================== */
