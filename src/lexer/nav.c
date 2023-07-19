// This file contains navigation functions for the lexer.

#include <stdlib.h>
#include <string.h>

#include <lexer/ch.h>
#include <lexer/nav.h>

/**
 * Advances the lexer to the next character in the input stream.
 * 
 * This function will also update current line, and column information, 
 * and detects the end of the l input stream (EOF)
 * 
 * @param self A pointer to a lexer object
 * 
 * @return void
 */
void __LEXER_consume_char(Lexer *self) {
    if (self->read_position >= self->input_length) {
        self->ch = '\0';
    }

    self->ch = self->input[self->read_position];

    if (self->ch == '\n') {
        self->column = 1;
        ++self->line;
    } else {
        ++self->column;
    }

    self->position = self->read_position;
    ++self->read_position;
}

/**
 * Read the next char from the lexer input.
 * 
 * @param self A pointer to a lexer object
 * 
 * @return The next char.
 */
chcode_t __LEXER_peek_next_char(Lexer *self) {
    if (self->read_position >= self->input_length) {
        return 0;
    }
    
    return self->input[self->read_position];
}

/**
 * Reads a sequence of characters from the lexer input based on the specified type.
 * 
 * @param self A pointer to a lexer object
 * 
 * @return A dynamically allocated string containing the read sequence, or NULL if there was an error.
 */
char* __LEXER_read_sequence(Lexer *self) {
    int position = self->position;

    while ((is_letter(self->ch) || is_numeric(self->ch) || self->ch == '.') ||
            // signed numbers will match with this condition
           ((self->ch == '-' || self->ch == '+') && is_numeric(__LEXER_peek_next_char(self)))) {
                __LEXER_consume_char(self);
    }

    int length = self->position - position;

    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    memcpy(result, self->input + position, length + 1);
    
    result[length] = '\0';

    // if (!is_valid_char_in_sequence(result[length])) {
    //     result[length] = '\0';
    // }

    return result;
}

/**
 * Skips over whitespace characters in the lexer input stream.
 *
 * @param self A pointer to a lexer objec
 * 
 * @return void
 */
void __LEXER_jump_whitespace(Lexer *self) {
    while (self->ch == ' ' || self->ch == '\t' || self->ch == '\n' || self->ch == '\r') {
        __LEXER_consume_char(self);
    }
}

