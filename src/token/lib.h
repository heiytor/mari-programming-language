#ifndef TOKEN_LIB_H
#define TOKEN_LIB_H

#include <langdef.h>
#include <token/def.h>

struct Token* new_token(char *literal, byte code, int line, int column);

struct Tokens *new_tokens_array();
void push_token(struct Tokens *array, struct Token *token);
void pop_tokens(struct Tokens *array);

void print_token(struct Token* tok);
uint8 get_ident_code(char* ident);
uint8 get_symbol_code(char *symbol);

#endif /* TOKEN_LIB_H */