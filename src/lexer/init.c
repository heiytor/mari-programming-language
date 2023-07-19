// This file includes the function for creating a new lexer object and initializing the lexer.

#include <stdlib.h>
#include <string.h>

#include <lexer/init.h>
#include <lexer/nav.h>
#include <lexer/tokenization.h>

/**
 * Creates a new lexer object for tokenizing the input string.
 *
 * @param input A pointer to the input string to be tokenized
 *
 * @return A pointer to the newly created lexer object
 */
Lexer* new_lexer(char* input) {
    Lexer *l = malloc(sizeof(Lexer));

    l->input = input;
    l->position = 0;
    l->read_position = 0;
    l->ch = 0;
    l->input_length = strlen(input);
    l->line = 1;
    l->column = 0;

    l->consume_char = __LEXER_consume_char;
    l->jump_whitespace = __LEXER_jump_whitespace;
    l->peek_next_char = __LEXER_peek_next_char;
    l->read_sequence = __LEXER_read_sequence;
    l->consume_token = __LEXER_consume_token;

    l->consume_char(l);

    return l;
}