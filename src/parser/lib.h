#ifndef PARSER_LIB_H
#define PARSER_LIB_H

#include <ast/def.h>
#include <lexer/def.h>
#include <parser/def.h>

struct Parser *new_parser(struct Lexer *lexer);

struct Program *__parse_program(struct Parser *self);
void __P_next_token(struct Parser *self);

#endif /* PARSER_LIB_H */