#ifndef PEX_PARSER_H
#define PEX_PARSER_H
#pragma once

#include "./lexer.hpp"
#include "./token.hpp"
#include "./AST.hpp"


class Parser {
    public:
        Parser(Lexer *lexer) {
            this->current = lexer->scan();
            this->lexer = lexer;
        }

        AST *parse();
        AST *parseStatement();
        AST *parseIdentifier();
        AST *parseEXPR();

        void expect(eToken type);

        Lexer *lexer;
        Token *current;
};

#endif
