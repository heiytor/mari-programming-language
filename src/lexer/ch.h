#ifndef LEXER_CH_H
#define LEXER_CH_H

#include <langdef.h>

int is_numeric(chcode_t ch);
int is_letter(chcode_t ch);
int is_allowed_as_first_char(chcode_t ch);
int is_compound_symbol(chcode_t curr_char, chcode_t next_char);
int is_number(chcode_t curr_char, chcode_t next_char);

#endif /* LEXER_CH_H */