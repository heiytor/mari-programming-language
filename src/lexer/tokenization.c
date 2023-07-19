// This file contains the core functions responsible for tokenizing input data in the lexer.

#include <stdio.h>
#include <string.h>

#include <lexer/ch.h>
#include <lexer/tokenization.h>
#include <token/lib.h>

/**
 * Reads a sequence of literal characters (letters and numbers) and creates a new token.
 * 
 * @param l A pointer to lexer object
 * @param curr_char The current char currently being processed
 * @param next_char The next char currently being processed. It is used only to identify the NUMBER code.
 * 
 * @returns A new token
 */
static Token *handle_literal(Lexer *l, chcode_t curr_char, chcode_t next_char) {
    char *curr_literal = l->read_sequence(l);
    uint8_t code = is_number(curr_char, next_char) == 1 ? NUMBER : ident_code(curr_literal);

    // get correct column value
    int column = l->column;
    if (column != 1) {
        column -= strlen(curr_literal);
    }

    return new_token(curr_literal, code, l->line, column);
}

/**
 * Reads a sequence of symbol characters and creates a new token.
 * 
 * @param l A pointer to lexer object
 * @param next_char The next char currently being processed. It is used only to identify compound symbols.
 * 
 * @returns A new token
 */
static Token *handle_symbol(Lexer *l, chcode_t next_char) {
    char compound_literal[3] = {l->ch, '\0', '\0'};
    int column = l->column;

    if (is_compound_symbol(compound_literal[0], next_char)) {
        compound_literal[1] = next_char;
        l->consume_char(l);
    }

    uint8_t code = symbol_code(compound_literal);
    return new_token(compound_literal, code, l->line, column);
}

/**
 * Advances the lexer's position in the input stream and creates a new token based on the current character being processed. This
 * function skips all whitespace characters (e.g. \n, \t).
 * 
 * @param self A pointer to lexer object
 * 
 * @returns A new token
 */
Token *__LEXER_consume_token(Lexer* self) {
    self->jump_whitespace(self);

    int is_char_allowed_for_start = is_allowed_as_first_char(self->ch);
    chcode_t curr_char = self->ch; // this will help us to get the NUMBER code instead IDENT when necessary
    chcode_t next_char = self->peek_next_char(self);

        // e.g my_var | my_var1
    if ((is_letter(self->ch) && is_char_allowed_for_start) ||
        // e.g +312 | -312542.423 | 312_542
        (is_number(self->ch, next_char))) {
            return handle_literal(self, curr_char, next_char);
    }

    Token *token = handle_symbol(self, next_char);
    
    self->consume_char(self);

    return token;
}
