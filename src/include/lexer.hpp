#ifndef PEX_LEXER_H
#define PEX_LEXER_H
#pragma once

#include <iostream>
#include <fstream>

#include "./token.hpp"

class Lexer {
    public:
        std::string source;
        int index = 0;

        char peek() {return source[index+1];}
        char advance() {index += 1; return source[index];}
        char current() {return source[index];}
        void skipws();

        Token *parseString();
        Token *parseInteger();
        Token *parseIdentifier();
        Token *scan();

        Lexer(std::string source) {
            this->source = source;
        }
};

#endif
