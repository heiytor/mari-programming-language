#ifndef LEXER_NAV_H
#define LEXER_NAV_H

#include <lexer/def.h>
#include <token/def.h>

void __LEXER_consume_char(Lexer *self);
char *__LEXER_read_sequence(Lexer *self);
void __LEXER_jump_whitespace(Lexer *self);
chcode_t __LEXER_peek_next_char(Lexer *self);

#endif /* LEXER_NAV_H */