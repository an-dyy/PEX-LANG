#include <iostream>
#include <fstream>

#include "include/PEX.hpp"
#include "include/AST.hpp"
#include "include/parser.hpp"
#include "include/lexer.hpp"
#include "include/token.hpp"


std::string prompt() {
    std::string capture;
    std::cout << "PEX> ";
    std::getline(std::cin, capture);

    capture.push_back('\0');
    return capture;
}

void pex_eval(Lexer *lexer) {
    if (lexer->source == "quit" || lexer->source == "exit") {
        exit(1);
    }

    else if (lexer->source == "clear") {
        std::cout<< u8"\033[2J\033[1;1H";
    }

    for (int i = 0; i < lexer->source.length(); i++) {
        Token *token = lexer->scan(); lexer->advance();
        switch(token->type) {
            case EOS: break;
            default:
                std::cout << TOKEN_STRINGS[(int)token->type] << " ";
                std::cout << token->value << std::endl;
        }
    }

    lexer->source = "";
    lexer->index = 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        Lexer *lexer = new Lexer("");

        while (true) {
            std::string input = prompt();
            lexer->source = input;
            pex_eval(lexer);
        }
    }

    else {
        std::string filepath = argv[1];
        std::ifstream file(filepath);
        std::string source;

        char token;
        while (file >> std::noskipws >> token) {
            source.push_back(token);
        }

        source.push_back('\0');
        file.close();
        
        Lexer *lexer = new Lexer(source);
        Parser *parser = new Parser(lexer);
        AST* root = parser->parse();
    }

    return 0;
}
