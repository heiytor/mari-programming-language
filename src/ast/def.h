#ifndef AST_DEFINITION_T
#define AST_DEFINITION_T

#include <token/def.h>

struct Statement {
    char* (*token_literal)(struct Token *tok);
    void (*statement_node)(struct Statement *self);
};

struct Expression {
    char* (*token_literal)(struct Token *tok);
    void (*expression_node)(struct Expression *self);
};

struct Program {
    struct Statement **statments;
    int statments_len;
};

struct Identifier {
    struct Expression *expression;
    struct Token *token;
    char *value;
};

struct Def_statement {
    struct Statement *statement;
    struct Token *token;
    struct Identifier *identifier; // name
    struct Expression *expression; // value
};

#endif /* AST_DEFINITION_T */