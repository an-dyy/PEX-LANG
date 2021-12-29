#include <iostream>

#include "include/PEX.hpp"
#include "include/lexer.hpp"
#include "include/token.hpp"


void compile_file(std::string filepath) {
    Lexer *lexer = new Lexer(filepath);
    for (int i = 0; i < lexer->source.size(); ++i) {
        Token *token = lexer->scan(); lexer->advance();
        std::string type = TOKEN_STRINGS[(int)token->type];
        printf("`%s` Type: %s\n", token->value.c_str(), type.c_str());
    }
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        compile_file(argv[i]);
    }

    return 0;
}
