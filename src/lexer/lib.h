#ifndef LEXER_LIB_H
#define LEXER_LIB_H

#include <lexer/def.h>
#include <token/def.h>

struct Lexer* new_lexer(char* input);

void __LEXER_consume_char(struct Lexer* lexer);
char* __LEXER_read_sequence(struct Lexer* lexer);
void __LEXER_jump_whitespace(struct Lexer* lexer);
byte __LEXER_peek_prev_char(struct Lexer* lexer);
byte __LEXER_peek_next_char(struct Lexer* lexer);
struct Token *__LEXER_consume_token(struct Lexer* lexer);

#endif /* LEXER_LIB_H */