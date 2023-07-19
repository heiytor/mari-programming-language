// This file provides functions for character recognition and handling.

#include <stdlib.h>
#include <string.h>

#include <lexer/ch.h>

/**
 * Determines whether a given character represents a number.
 * 
 * @param ch The character being evaluated.
 * 
 * @return 1 if the character is numeric, 0 otherwise.
 */
int is_numeric(chcode_t ch) {
    return '0' <= ch && ch <= '9';
}

/**
 * Some programming languages allow special characters for variable declaration, such as "$" in
 * Javascript. To accommodate this, during tokenization, this character must be considered a
 * letter just like any other [a-zA-Z]. 
 * 
 * During the syntax creation process, one of my main goals was to maintain readable code, for
 * this reason, as a personal choice, I decided to make characters like "?" and "!" available
 * for variable declaration. This happens because I believe that a function written for example
 * as "is_char?()" can be much simpler to understand for an inexperienced person than simply
 * "is_char".
 * 
 * A number of other special characters are available for the same reason (or simply to give
 * freedom to the developer).
 *
 * @param ch The character being evaluated.
 * 
 * @return 1 if the character is a letter, 0 otherwise.
 */
int is_letter(chcode_t ch) {
    return 'a' <= ch && ch <= 'z' ||
           'A' <= ch && ch <= 'Z' ||
           // Add special characters above
           ch == '_' ||
           // ch == '-' || // uncomment to allow kebab-case
           ch == '?' ||
           ch == '!' ||
           ch == '$';
}

/**
 * Checks if the character sequence forms a compound symbol.
 * 
 * @param curr_char The current character being evaluated.
 * @param next_char The character following the current character.
 * 
 * @return 1 if the characters form a compound symbol, 0 otherwise.
 */
int is_compound_symbol(chcode_t curr_char, chcode_t next_char) {
    int actual = curr_char == '+' || curr_char == '-' || curr_char == '=' || curr_char == '!' || curr_char == '*' || curr_char == '<' || curr_char == '>';
    int next = next_char == '+' || next_char == '-' || next_char == '=' || next_char == '!' || next_char == '*' || next_char == '<' || next_char == '>';

    return actual != 0 && next != 0;
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
 * This function, `is_number()`, is used to determine whether a given character 
 * sequence represents a number. This includes both signed numbers, where the first 
 * character is a sign ('-' or '+') followed by a numeric character, as well as 
 * unsigned numbers, where the character is numeric. It returns true if the first 
 * character is numeric or if it's a sign and the second character is numeric. 
 * Otherwise, it returns false.
 * 
 * @param curr_char The current character being evaluated. This could be a numeric 
 * character or a sign ('+' or '-').
 * 
 * @param next_char The character following the current character. Used for evaluating 
 * if a sequence is representing a signed number.
 * 
 * @return 1 if is number, 0 otherwise.
 */
int is_number(chcode_t curr_char, chcode_t next_char) {
    return (is_numeric(curr_char) || ((curr_char == '-' || curr_char == '+') && is_numeric(next_char)));
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
 * 
 * @param ch The current character being evaluated.
 * 
 * @return 1 if is number, 0 otherwise.
 */
int is_allowed_as_first_char(chcode_t ch) {
    return ch != '.' &&
        // ch != '-' && // uncomment to allow kebab-case
           ch != '?' &&
           ch != '!';
}