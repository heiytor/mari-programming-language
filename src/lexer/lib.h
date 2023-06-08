#ifndef LEXER_LIB_H
#define LEXER_LIB_H

#include <lexer/def.h>
#include <token/def.h>

struct Lexer* new_lexer(char* input);

void __next_char(struct Lexer* l);
char* __read_sequence(struct Lexer* l);
void __jump_whitespace(struct Lexer* l);
byte __peek_prev_char(struct Lexer *l);
byte __peek_next_char(struct Lexer *l);
struct Token *__next_token(struct Lexer *l);

#endif /* LEXER_LIB_H */