#ifndef TOKEN_ACTIONS_H
#define TOKEN_ACTIONS_H

#include <types.h>

#include <lexer/actions.h>

#include <token/structs.h>

struct Token* new_token(char *literal, byte code, int line, int column);
struct Token* next_token(struct Lexer *lex);
void print_token(struct Token* tok);

// Array

struct Tokens *init_token_arr();
void push_token(struct Tokens *tok_arr, struct Token *tok);
void pop_tokens(struct Tokens *tok_arr);

#endif /* TOKEN_ACTIONS_H */