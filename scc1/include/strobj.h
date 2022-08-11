/* ===================================================================== */
/* ===================================================================== */

#pragma once

#include "comp.h"

/* ===================================================================== */

typedef struct StringTAG String;

/* ===================================================================== */

RET_NOTNULL
String* new_string(const char* rhs);

RET_NOTNULL
String* new_stringn(const char* rhs, size_t len);

RET_NOTNULL
String* new_stringCopy(const String* rhs);

void delete_string(String*);

/* ===================================================================== */

const char* string_c(const String* this);

/* ===================================================================== */

int string_cmpc(const String* lhs, const char* rhs);

int string_cmpn(const String* lhs, const char* rhs, size_t len);

int string_cmp(const String* lhs, const String* rhs);

/* ===================================================================== */

RET_NOTNULL
String* string_catc(String* dest, const char* source);

RET_NOTNULL
String* string_catn(String* dest, const char* source, size_t len);

RET_NOTNULL
String* string_cat(String* dest, const String* rhs);

/* ===================================================================== */

