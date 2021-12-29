#ifndef PEX_TOKEN_H
#define PEX_TOKEN_H
#pragma once

#include <iostream>
#include <map>

#define TOKENS \
    tok(ID, "IDENTIFIER") \
    tok(STR, "LITERAL STRING") \
    tok(INT, "LITERAL INTEGER") \
    tok(FUNC, "FUNC") \
    tok(WHILE, "WHILE") \
    tok(FOR, "FOR") \
    tok(SEMI, "SEMI") \
    tok(OP_ADD, "OP_ADD") \
    tok(OP_SUB, "OP_SUB") \
    tok(OP_MUL, "OP_MUL") \
    tok(OP_DIV, "OP_DIV") \
    tok(OP_MOD, "OP_MOD") \
    tok(OP_ASSIGN, "OP_ASSIGN") \
    tok(OP_EQ, "OP_EQ") \
    tok(OP_NE, "OP_NE") \
    tok(OP_AND, "OP_AND") \
    tok(OP_OR, "OP_OR") \
    tok(BIT_AND, "BIT_AND") \
    tok(BIT_OR, "BIT_OR") \
    tok(LPAREN, "LPAREN") \
    tok(RPAREN, "RPAREN") \
    tok(LBRACE, "LBRACE") \
    tok(RBRACE, "RBRACE") \
    tok(LBRACK, "LBRACK") \
    tok(RBRACK, "RBRACK") \
    tok(EOS, "END OF FILE") \

typedef enum {
    #define tok(token, value) token,
    TOKENS
    #undef tok

} eToken;

const std::map<std::string, eToken> RESERVED = {
    {"func", FUNC},
    {"for", FOR},
    {"while", WHILE},
};

const std::string TOKEN_STRINGS[] = {
    #define tok(token, value) value,
    TOKENS
    #undef tok
};

class Token {
    public:
        Token(eToken type, std::string value) {
            this->type = type;
            this->value = value;
        }

        eToken type;
        std::string value;
};

#endif
