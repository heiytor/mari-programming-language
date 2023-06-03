#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <helpers/characters.h>
#include <types.h>

/**
 * TODO:
 *      Add more numbers support.
 */
bool is_numeric(byte ch) {
    return '0' <= ch && ch <= '9';
}


bool is_letter(byte ch) {
    return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

bool is_compound_symbol(byte curr_char, byte next_char) {
    bool actual = curr_char == '+' || curr_char == '-' || curr_char == '=' || curr_char == '!' || curr_char == '*' || curr_char == '<' || curr_char == '>';
    bool next = next_char == '+' || next_char == '-' || next_char == '=' || next_char == '!' || next_char == '*' || next_char == '<' || next_char == '>';

    return actual == true && next == true;
}