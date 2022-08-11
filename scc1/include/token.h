/* ===================================================================== */
/* ===================================================================== */

#pragma once

#include "comp.h"

/* ===================================================================== */

typedef enum TokenTypeTAG
{
    // Values below 0x00000100 are ASCII character literals.

    TOK_EndOfFile    = 0x00000005, // End of file marker (used by lexer to signal EOF)

    TOK_Identifier   = 0x00000100,

    // Constant Values
    TOK_ConstString  = 0x00000101, // String
    TOK_ConstChar    = 0x00000102, // Char
    TOK_ConstShort   = 0x00000103, // Short
    TOK_ConstInt     = 0x00000104, // Int
    TOK_ConstLong    = 0x00000105, // Long
    TOK_ConstLLong   = 0x00000106, // Long Long
    TOK_ConstFloat   = 0x00000107, // Float
    TOK_ConstDouble  = 0x00000108, // Double
    TOK_ConstLDouble = 0x00000109, // Long Double

    // Keywords
    KW_DO        = 0x00001200,
    KW_IF        = 0x00001201,

    KW_FOR       = 0x00001300,
    KW_INT       = 0x00001301,

    KW_AUTO      = 0x00001400,
    KW_CASE      = 0x00001401,
    KW_CHAR      = 0x00001402,
    KW_ELSE      = 0x00001403,
    KW_ENUM      = 0x00001404,
    KW_GOTO      = 0x00001405,
    KW_LONG      = 0x00001406,
    KW_VOID      = 0x00001407,

    KW_BREAK     = 0x00001500,
    KW_CONST     = 0x00001501,
    KW_FLOAT     = 0x00001502,
    KW_SHORT     = 0x00001503,
    KW_UNION     = 0x00001504,
    KW_WHILE     = 0x00001505,

    KW_DOUBLE    = 0x00001600,
    KW_EXTERN    = 0x00001601,
    KW_RETURN    = 0x00001602,
    KW_SIGNED    = 0x00001603,
    KW_SIZEOF    = 0x00001604,
    KW_STATIC    = 0x00001605,
    KW_STRUCT    = 0x00001606,
    KW_SWITCH    = 0x00001607,

    KW__INT_8    = 0x00001690, ///< Nonstandard _int_8
    
    KW_DEFAULT   = 0x00001700,
    KW_TYPEDEF   = 0x00001701,

    KW__INT_16   = 0x000017A0, ///< Nonstandard _int_16
    KW__INT_32   = 0x000017A1, ///< Nonstandard _int_32
    KW__INT_64   = 0x000017A2, ///< Nonstandard _int_64

    KW_CONTINUE  = 0x00001800,
    KW_REGISTER  = 0x00001801,
    KW_UNSIGNED  = 0x00001802,
    KW_VOLATILE  = 0x00001803,

    // Multi symbol tokens
    SYM_INC      = 0x00002000, // ++
    SYM_DEC      = 0x00002001, // --
    SYM_SHL      = 0x00002002, // <<
    SYM_SHR      = 0x00002003, // >>
    SYM_LE       = 0x00002004, // <=
    SYM_GE       = 0x00002005, // >=
    SYM_AND      = 0x00002006, // &&
    SYM_OR       = 0x00002007, // ||
    SYM_EQ       = 0x00002008, // ==
    SYM_NE       = 0x00002009, // !=

    ASGN_ADD     = 0x00002100, // +=
    ASGN_SUB     = 0x00002101, // -=
    ASGN_MUL     = 0x00002102, // *=
    ASGN_DIV     = 0x00002103, // /=
    ASGN_MOD     = 0x00002104, // %=
    ASGN_AND     = 0x00002105, // &=
    ASGN_OR      = 0x00002106, // |=
    ASGN_XOR     = 0x00002107, // ^=

    ASGN_SHL     = 0x00003000, // <<=
    ASGN_SHR     = 0x00003001, // >>=
    SYM_ELIPSE   = 0x00003002, // ...
} TokenType;

/* ===================================================================== */

typedef struct StringTAG String;

typedef struct TokenTAG
{
    String* lit;            ///< Token literal string
    TokenType type;         ///< Token type
    const String* filename; ///< The filename we saw this token in. (unowned)
    int lineNumber;         ///< The line number we saw this token on.
} Token;

/* ===================================================================== */

RET_NOTNULL
Token* new_token(String* lit, TokenType type, int lineNumber, const String* filename);
void delete_token(Token*);

/* ===================================================================== */
