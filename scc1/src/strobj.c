/* ===================================================================== */
/* ===================================================================== */

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "strobj.h"

/* ===================================================================== */

// For now bytes/chars are basically the same thing, we don't support Unicode. -- B.Simonds (Aug 11, 2022)

typedef struct StringTAG
{
    char* data;      ///< Actual string data.
    size_t length;   ///< Length in characters of string data.
    size_t size;     ///< Size of data buffer in bytes.
} String;

/* ===================================================================== */

RET_NOTNULL
String* new_string(const char* rhs)
{
    size_t len = strlen(rhs);
    return new_stringn(rhs, len);
}

RET_NOTNULL
String* new_stringn(const char* rhs, size_t len)
{
    String* rval = (String*)safe_alloc(sizeof(String));

    rval->length = len;
    rval->size = len + 1;
    rval->data = (char*)safe_alloc(rval->size);

    strncpy(rval->data, rhs, rval->length);
    rval->data[rval->length] = '\0';

    return rval;
}

RET_NOTNULL
String* new_stringCopy(const String* rhs)
{
    String* rval = (String*)safe_alloc(sizeof(String));

    rval->length = rhs->length;
    rval->size = rhs->size;
    rval->data = (char*)safe_alloc(rval->size);

    strncpy(rval->data, rhs->data, rval->size);

    return rval;
}

void delete_string(String* this)
{
    if (!this)
        return;

    free(this->data);

    free(this);
}

/* ===================================================================== */

const char* string_c(const String* this)
{
    return this->data;
}

/* ===================================================================== */

int string_cmpc(const String* lhs, const char* rhs)
{
    return string_cmpn(lhs, rhs, strlen(rhs));
}

int string_cmpn(const String* lhs, const char* rhs, size_t len)
{
    size_t x = MIN(lhs->length, len);

    return strncmp(lhs->data, rhs, x);
}

int string_cmp(const String* lhs, const String* rhs)
{
    return string_cmpn(lhs, rhs->data, rhs->length);
}

/* ===================================================================== */

RET_NOTNULL
String* string_catc(String* dest, const char* str)
{
    return string_catn(dest, str, strlen(str));
}

RET_NOTNULL
String* string_catn(String* dest, const char* str, size_t len)
{
    size_t newLen = dest->length + len;
    char* newData = (char*)safe_alloc(newLen + 1);

    memcpy(newData, dest->data, dest->length);
    memcpy(newData + dest->length, str, len);
    newData[newLen] = '\0';

    free(dest->data);
    dest->data = newData;
    dest->length = newLen;
    dest->size = newLen + 1;

    return dest;
}

RET_NOTNULL
String* string_cat(String* lhs, const String* rhs)
{
    return string_catn(lhs, rhs->data, rhs->length);
}

/* ===================================================================== */
