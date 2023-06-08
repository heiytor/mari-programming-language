#ifndef HELPERS_METHODS_T
#define HELPERS_METHODS_T

#include <langdef.h>
#include <stdbool.h>

bool is_numeric(byte ch);

bool is_letter(byte ch);

bool is_allowed_as_first_char(byte ch);

bool is_compound_symbol(byte curr_char, byte next_char);

bool is_signed_number(byte curr_char, byte next_char);

#endif /* HELPERS_METHODS_T */