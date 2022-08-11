/* ===================================================================== */
/* ===================================================================== */

#pragma once

#include "comp.h"

/* ===================================================================== */

// We may need to make this opaque. -- B.Simonds (Aug 11, 2022)
typedef struct StringTAG
{
    char*  m_data;      ///< Actual string data.
    size_t m_length;    ///< Length in bytes of string data.
} String;

/* ===================================================================== */

RET_NOTNULL
String* new_string(const char* rhs);

RET_NOTNULL
String* new_stringn(const char* rhs, size_t len);

RET_NOTNULL
String* new_stringCopy(const String* rhs);

void delete_string(String*);

/* ===================================================================== */

RET_NOTNULL
String* string_cat(String* lhs, String* rhs);

/* ===================================================================== */

