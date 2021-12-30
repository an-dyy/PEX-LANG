#ifndef PEX_AST_H
#define PEX_AST_H

#include <iostream>
#include <vector>

#include "./token.hpp"

#define AST_TYPES \
    a(AST_COMPOUND, "AST_COMPOUND") \
    a(AST_VAR_DEF, "AST_VAR_DEF") \
    a(AST_VAR, "AST_VAR") \
    a(AST_FUNC, "AST_FUNC") \
    a(AST_FUNC_CALL, "AST_FUNC_CALL") \
    a(AST_BINOP, "AST_BINOP") \
    a(AST_ID, "AST_ID") \
    a(AST_INT, "AST_INT") \
    a(AST_STR, "AST_STR") \
    a(AST_NULL, "AST_NULL") \

typedef enum {
    #define a(type, value) type,
    AST_TYPES
    #undef a

} eAST;

const std::string AST_STRINGS[] = {
    #define a(type, value) value,
    AST_TYPES
    #undef a
};

class AST {
    public:
        AST(eAST type) {
            this->type = type;
        }

        eAST type;
        AST *value;
        AST *right;
        AST *left;

        Token *op;

        int int_value;
        std::string str_value;

        std::string name;
        std::vector<AST*> compound;
};

#endif
