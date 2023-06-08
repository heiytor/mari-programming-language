#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <utils/chardef.h>
#include <langdef.h>

bool is_numeric(byte ch) {
    return '0' <= ch && ch <= '9';
}


bool is_letter(byte ch) {
    return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_' || ch == '?' || ch == '!';
}

bool is_compound_symbol(byte curr_char, byte next_char) {
    bool actual = curr_char == '+' || curr_char == '-' || curr_char == '=' || curr_char == '!' || curr_char == '*' || curr_char == '<' || curr_char == '>';
    bool next = next_char == '+' || next_char == '-' || next_char == '=' || next_char == '!' || next_char == '*' || next_char == '<' || next_char == '>';

    return actual == true && next == true;
}

/**
 * In many programming languages, numeric literals can include a sign (+ or -) to 
 * indicate whether the number is positive or negative. However, this sign is not 
 * considered part of the number itself; it's treated as an operator that operates 
 * on the number.
 *
 * For instance, in the expression "-5", the "-" is a unary negation operator that 
 * operates on the number "5". Similarly, in the expression "+5", the "+" is a unary 
 * plus operator.
 *
 * This function, `is_signed_number()`, is used to determine whether a given character 
 * sequence represents a signed number in this way. It returns true if the first character 
 * is a sign ('-' or '+') and the second character is numeric. Otherwise, it returns false.
 */
bool is_signed_number(byte curr_char, byte next_char) {
    return curr_char == '-' && is_numeric(next_char); // || curr_char == '+' && is_numeric(next_char);
}

/**
 * As in other languages, some special characters are allowed to create variable names,
 * but you are not allowed to start with these characters.
 *
 * Let's take "!" for example:
 * 
 * ! is an operator character, if the lexer sees a !, it must
 * create a specific token for it. Even so, if the language considers "!" as a letter
 * (to create var names), so the lexer will tokenize it as a variable. Because of this,
 * some languages must block these special characters to be the first letter of the var.
 * 
 * So if the lexer sees any of these special characters, it must create two tokens:
 * !my_var: one for "!" and other for "my_var"
 * 
 * If the lexer sees any of these characters after a letter, the lexer must create a single token:
 * my_!var: "my_!var"
*/
bool is_allowed_as_first_char(byte ch) {
    return ch != '.' && ch != '?' && ch != '!';
}