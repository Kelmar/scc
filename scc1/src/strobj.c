/* ===================================================================== */
/* ===================================================================== */

#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "strobj.h"

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

    rval->m_length = len + 1;
    rval->m_data = (char*)safe_alloc(rval->m_length);

    strncpy(rval->m_data, rhs, rval->m_length - 1);
    rval->m_data[rval->m_length - 1] = '\0';

    return rval;
}

RET_NOTNULL
String* new_stringCopy(const String* rhs)
{
    String* rval = (String*)safe_alloc(sizeof(String));

    rval->m_length = rhs->m_length;
    rval->m_data = (char*)safe_alloc(rval->m_length);

    strncpy(rval->m_data, rhs->m_data, rval->m_length - 1);
    rval->m_data[rval->m_length - 1] = '\0';

    return rval;
}

void delete_string(String* this)
{
    if (!this)
        return;

    free(this->m_data);

    free(this);
}

/* ===================================================================== */

RET_NOTNULL
String* string_cat(String* lhs, String* rhs)
{
    String* rval = (String*)safe_alloc(sizeof(String));

    rval->m_length = lhs->m_length + rhs->m_length + 1;
    rval->m_data = (char*)safe_alloc(rval->m_length);

    memcpy(rval->m_data, lhs->m_data, lhs->m_length);
    memcpy(rval->m_data + lhs->m_length, rhs->m_data, rhs->m_length);
    rval->m_data[rval->m_length] = '\0';

    return rval;
}

/* ===================================================================== */
