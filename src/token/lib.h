#ifndef TOKEN_DEF_H
#define TOKEN_DEF_H

#include <langdef.h>
#include <token/def.h>

struct Token* new_token(char *literal, byte code, int line, int column);
void print_token(struct Token* tok);

struct Tokens *init_token_arr();
void push_token(struct Tokens *tok_arr, struct Token *tok);
void pop_tokens(struct Tokens *tok_arr);

uint8 get_ident_code(char* ident);
uint8 get_symbol_code(char *symbol);

#endif /* TOKEN_DEF_H */