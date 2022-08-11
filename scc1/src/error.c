/* ===================================================================== */
/* ===================================================================== */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "strobj.h"

/* ===================================================================== */

int g_errorCount = 0;
int g_warnCount = 0;

/* ===================================================================== */

int getErrorCount(void) { return g_errorCount; }
int getWarnCount (void) { return g_warnCount; }

/* ===================================================================== */

void verror(Token* token, ErrorCode errorCode, const char* message, va_list args)
{
    char buf[1024];
    vsnprintf(buf, sizeof(buf), message, args);

    if (token)
        fprintf(stderr, "%s(%d): error C%04d: %s\r\n", string_c(token->filename), token->lineNumber, errorCode, buf);
    else
        fprintf(stderr, "error C%04d: %s\r\n", errorCode, buf);
}

/* ===================================================================== */

void fatal(Token* token, ErrorCode errorCode, const char* message, ...)
{
    va_list args;
    
    va_start(args, message);
    verror(token, errorCode, message, args);
    va_end(args);

    exit(1);
}

/* ===================================================================== */

void error(Token* token, ErrorCode errorCode, const char* message, ...)
{
    ++g_errorCount;

    va_list args;

    va_start(args, message);
    verror(token, errorCode, message, args);
    va_end(args);
}

/* ===================================================================== */

void warn(Token* token, ErrorCode errorCode, const char* message, ...)
{
    ++g_warnCount;

    va_list args;

    va_start(args, message);
    verror(token, errorCode, message, args);
    va_end(args);
}

/* ===================================================================== */
