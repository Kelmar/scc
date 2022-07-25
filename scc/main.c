#include <stdio.h>
#include <string.h>

#include "lexer.h";

/*
 * Stage 1 compiling.
 * 
 * This occurs after the preprocessor has done it's thing.
 * 
 * We need to keep an eye out for "#line" directives while lexing; that will
 * change the file name and line number, which we'll need for error reporting.
 */

char* g_filename;

void parseArgs(int argc, const char** argv)
{
    g_filename = (char*)argv[1];
}

void mainLoop(Lexer* l)
{
    for (;;)
    {
        Token* t = lexer_getToken(l);

        if (!t)
            break;

        printf("0x%08X TOKEN: %s\r\n", t->type, t->lit);

        delete_token(t);
    }

    delete_lexer(l);
}

int main(int argc, const char** argv)
{
    parseArgs(argc, argv);

    Lexer* l = new_lexer(g_filename);
    int err = lexer_lastError(l);

    if (err != 0)
    {
        char* errStr = strerror(err);
        fprintf(stderr, "Unable to open file '%s': %s\r\n", g_filename, errStr);
        return 1;
    }

    mainLoop(l);

    return 0;
}
