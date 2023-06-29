#ifndef HELPERS_METHODS_T
#define HELPERS_METHODS_T

#include <langdef.h>
#include <stdbool.h>

int is_numeric(byte ch);
int is_letter(byte ch);
int is_allowed_as_first_char(byte ch);
int is_compound_symbol(byte curr_char, byte next_char);
int is_number(byte curr_char, byte next_char);

#endif /* HELPERS_METHODS_T */