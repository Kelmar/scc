/* ===================================================================== */
/* ===================================================================== */

#pragma once

#include <stdlib.h>
#include <string.h>

#include "comp.h"
#include "token.h"

/* ===================================================================== */

typedef enum ErrorCodeTAG
{
    ERR_CantOpenFile  = 1000,
    ERR_OutOfMemory   = 1001,
    ERR_InternalError = 1002,

    ERR_UnknownType   = 2000,
} ErrorCode;

/* ===================================================================== */

int getErrorCount(void);
int getWarnCount(void);

/* ===================================================================== */

DECL_NORET
void fatal(Token* t, ErrorCode errCode, const char* message, ...);

void error(Token* t, ErrorCode errCode, const char* message, ...);
void warn (Token* t, ErrorCode errCode, const char* message, ...);

/* ===================================================================== */

RET_NOTNULL
inline void* safe_alloc(size_t sz)
{
    void* rval = malloc(sz);

    if (!rval)
    {
        fatal(NULL, ERR_OutOfMemory, "Out of memory");
        exit(1); // Makes the microsoft compiler happy
    }

    memset(rval, 0, sz);
    return rval;
}

/* ===================================================================== */

RET_NOTNULL
inline char* safe_dup(const char* str)
{
    size_t len = strlen(str);
    char* rval = (char*)safe_alloc(len + 1);
    strncpy(rval, str, len);
    rval[len] = '\0';
    return rval;
}

/* ===================================================================== */

RET_NOTNULL
inline char* safe_slice(const char* str, int len)
{
    char* rval = (char*)safe_alloc(len + 1);
    strncpy(rval, str, len);
    rval[len] = '\0';
    return rval;
}

/* ===================================================================== */
