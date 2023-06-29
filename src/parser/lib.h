#ifndef PARSER_LIB_H
#define PARSER_LIB_H

#include <langdef.h>

#include <ast/def.h>
#include <lexer/def.h>
#include <parser/def.h>

struct Parser* new_parser(struct Lexer* lexer);

void __PARSER_consume_token(struct Parser* self);
int __PARSER_curr_token_is(struct Parser* self, uint8 code);
int __PARSER_next_token_is(struct Parser* self, uint8 code);
int __PARSER_consume_or_ignore_if_next_token_is(struct Parser* self, uint8 code);

struct Program* __PARSER_parse_program(struct Parser* self);
struct Statement* __PARSER_parse_statement(struct Parser* self);
struct Statement* __PARSER_parse_var_statement(struct Parser* self);
struct Statement* __PARSER_parse_return_statement(struct Parser* self);
struct Statement* __PARSER_parse_expression_statement(struct Parser* self);

void __PARSE_push_error(struct Parser* self, char* template);
void __PARSE_print_error(struct Parser* self);

#endif /* PARSER_LIB_H */