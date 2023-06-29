#include <string.h>
#include <stdlib.h>

#include <lexer/lib.h>

/**
 * Creates a new lexer object for tokenizing the input string.
 *
 * @param input A pointer to the input string to be tokenized
 *
 * @return A pointer to the newly created lexer object
 */
struct Lexer* new_lexer(char* input) {
    struct Lexer *lex = malloc(sizeof(struct Lexer));

    lex->input = input;
    lex->position = 0;
    lex->read_position = 0;
    lex->ch = 0;
    lex->input_length = strlen(input);
    lex->line = 1;
    lex->column = 0;

    lex->consume_char = __LEXER_consume_char;
    lex->jump_whitespace = __LEXER_jump_whitespace;
    lex->peek_next_char = __LEXER_peek_next_char;
    lex->peek_prev_char = __LEXER_peek_prev_char;
    lex->read_sequence = __LEXER_read_sequence;
    lex->consume_token = __LEXER_consume_token;

    lex->consume_char(lex);

    return lex;
}