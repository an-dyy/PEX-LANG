#include <iostream>

#include "include/parser.hpp"
#include "include/AST.hpp"
#include "include/token.hpp"


void Parser::expect(eToken type) {
    this->lexer->advance();
    this->current = this->lexer->scan();

    if (this->current->type != type) {
        std::cout << "Unexpected token: " << this->current->value;
        std::cout << " With type: " << TOKEN_STRINGS[(int)this->current->type];
        std::cout << std::endl;
        exit(1);
    }
}

AST *Parser::parseEXPR() {
    AST *expr = new AST(AST_NULL);
    switch(this->current->type) {
        case INT: {
            expr->type = AST_INT;
            expr->int_value = std::stoi(this->current->value);

            return expr;
        }

        case STR: {
            expr->type = AST_STR;
            expr->str_value = this->current->value;

            return expr;
        }

        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
        case OP_MOD: {
            expr->type = AST_BINOP;
            expr->left = this->root->compound.back();
            expr->op = this->current;

            this->lexer->advance();
            this->current = this->lexer->scan();
            this->root->compound.pop_back();

            expr->right = this->parseEXPR();
            return expr;
        }

        default: std::cout << "Not an expression.";
            exit(1);
    }
}

AST *Parser::parseIdentifier() {
    this->lexer->advance();
    this->lexer->skipws();

    AST *variable = new AST(AST_NULL);
    switch(this->lexer->current()) {
        case '=': {
            variable->type = AST_VAR_DEF;
            variable->name = this->current->value;

            this->lexer->advance();
            this->current = this->lexer->scan();

            variable->value = this->parseEXPR();
            
            this->expect(SEMI);
            return variable;
        }

        default: {
            variable->type = AST_VAR;
            variable->name = this->current->value;

            return variable;
        }
    }
}


AST *Parser::parseStatement() {
    switch(this->current->type) {
        case ID: return this->parseIdentifier();
        default: return this->parseEXPR();
    }
}

AST *Parser::parse() {
    AST *root = new AST(AST_COMPOUND);
    this->root = root;

    while (this->current->type != EOS) {
        root->compound.push_back(this->parseStatement());
        this->lexer->advance();

        this->current = \
            this->lexer->scan();
    }

    for (const AST* child : root->compound) {
        if (child->type == AST_BINOP) {
            std::cout << AST_STRINGS[(int)child->left->type] << " ";
            std::cout << child->left->int_value << std::endl;
            std::cout << TOKEN_STRINGS[(int)child->op->type] << std::endl;
            std::cout << AST_STRINGS[(int)child->right->type] << " ";
            std::cout << child->right->int_value << std::endl;
        }
        
        else {
            std::cout << AST_STRINGS[(int)child->type] << " ";
            std::cout << child->value << std::endl;
        }
    }

    return root;
}
