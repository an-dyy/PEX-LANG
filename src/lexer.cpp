#include <iostream>

#include "include/token.hpp"
#include "include/lexer.hpp"

#define nTok(type, value) {return new Token(type, value);}


void Lexer::skipws() {
    while (std::isspace(this->current())) {
        this->advance();
    }
}

Token * Lexer::parseString() {
    char quote = this->current();
    std::string value{quote, this->advance()};

    while (this->current() != quote) {
        value.push_back(this->advance());

        if (this->peek() == quote) {
            value.push_back(this->advance());
        }
    }

    nTok(STR, value);
}

Token * Lexer::parseInteger() {
    std::string value{this->current()};

    while (std::isdigit(this->peek())) {
        value.push_back(this->advance());
    }

    nTok(INT, value);
}

Token * Lexer::parseIdentifier() {
    std::string value{this->current()};

    while (std::isalpha(this->peek())) {
        value.push_back(this->advance());
    }

    if (RESERVED.find(value) != RESERVED.end()) {
        nTok(RESERVED.at(value), value);
    }

    nTok(ID, value);
}

Token * Lexer::scan() {
    this->skipws();

    char token = this->current();
    std::string value{token};

    if (std::isdigit(token)) {return this->parseInteger();}
    else if (std::isalpha(token)) {return this->parseIdentifier();}

    switch(token) {
        case '\'':
        case '"': return this->parseString();
        case '=': nTok(OP_ASSIGN, value);
        case '+': nTok(OP_ADD, value);
        case '-': nTok(OP_SUB, value);
        case '*': nTok(OP_MUL, value);
        case '/': nTok(OP_DIV, value);
        case '%': nTok(OP_MOD, value);
        case '(': nTok(LPAREN, value);
        case ')': nTok(RPAREN, value);
        case '{': nTok(LBRACE, value);
        case '}': nTok(RBRACE, value);
        case '[': nTok(LBRACK, value);
        case ']': nTok(RBRACK, value);
        case ';': nTok(SEMI, value);
        case '\0': nTok(EOS, value);
        default: printf("Err: Illegal character: %c, ASCII: %i\n", token, (int)token);
            exit(1);
    }
}
