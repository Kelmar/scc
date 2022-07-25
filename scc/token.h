#pragma once

typedef enum TokenTypeTAG
{
    // Values below 0x00000100 are ASCII character literals.

    EndOfFile = 0x00000005, // End of file marker (used by lexer to signal EOF)

    IDENTIFIER = 0x00000100,

    // Constants
    CONST_STRING = 0x00000101,
    CONST_CHAR = 0x00000102,
    CONST_SHORT = 0x00000103,
    CONST_INT = 0x00000104,
    CONST_LONG = 0x00000105,
    CONST_ULONG = 0x00000106,
    CONST_FLOAT = 0x00000107,
    CONST_DOUBLE = 0x00000108,

    // Keywords
    KW_DO = 0x00001200,
    KW_IF = 0x00001201,

    KW_FOR = 0x00001300,

    // Multi symbol tokens
    SYM_INC = 0x00002000, // ++
    SYM_DEC = 0x00002001, // --
    SYM_SHL = 0x00002002, // <<
    SYM_SHR = 0x00002003, // >>
    SYM_LE = 0x00002004, // <=
    SYM_GE = 0x00002005, // >=
    SYM_AND = 0x00002006, // &&
    SYM_OR = 0x00002007, // ||
    SYM_EQ = 0x00002008, // ==
    SYM_NE = 0x00002009, // !=

    ASGN_ADD = 0x00002100, // +=
    ASGN_SUB = 0x00002101, // -=
    ASGN_MUL = 0x00002102, // *=
    ASGN_DIV = 0x00002103, // /=
    ASGN_MOD = 0x00002104, // %=
    ASGN_AND = 0x00002105, // &=
    ASGN_OR = 0x00002106, // |=
    ASGN_XOR = 0x00002107, // ^=

    ASGN_SHL = 0x00003000, // <<=
    ASGN_SHR = 0x00003001, // >>=
    SYM_ELIPSE = 0x00003002, // ...
} TokenType;

typedef struct TokenTAG
{
    char* lit;
    TokenType type;
    int lineNumber;
} Token;

Token* new_token(const char* lit, int litLen, TokenType type, int lineNumber);
void delete_token(Token*);
