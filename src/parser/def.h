#ifndef PARSER_DEFINITION_H
#define PARSER_DEFINITION_H

#include <ast/def.h>
#include <lexer/def.h>
#include <token/def.h>

struct Parser {
    struct Lexer *lexer;

    struct Token *curr_tok;
    struct Token *next_tok;

    void (*next_token)(struct Parser *self);
    struct Program *(*parse_program)(struct Parser *self);
};

#endif /* PARSER_DEFINITION_H */