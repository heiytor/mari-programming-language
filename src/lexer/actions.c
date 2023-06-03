#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <helpers/characters.h>

#include <lexer/actions.h>

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

    next_char(lex);

    return lex;
}

/**
 * Advances the lexer to the next character in the input stream.
 * 
 * This function will also update current line, and column information, 
 * and detects the end of the lexer input stream (EOF)
 * 
 * @param lex A pointer to a lexer object
 * 
 * @return void
 */
void next_char(struct Lexer* lex) {
    if (lex->read_position >= lex->input_length) {
        lex->ch = '\0';
    }

    lex->ch = lex->input[lex->read_position];

    if (lex->ch == '\n') {
        lex->column = 1;
        ++lex->line;
    } else {
        ++lex->column;
    }

    lex->position = lex->read_position;
    ++lex->read_position;
}

byte peek_next_char(struct Lexer *lexer) {
    if (lexer->read_position >= lexer->input_length) {
        return 0;
    }
    
    return lexer->input[lexer->read_position];
}

/**
 * Reads a sequence of characters from the lexer input based on the specified type.
 * 
 * @param lex A pointer to a lexer object
 * 
 * @return A dynamically allocated string containing the read sequence, or NULL if there was an error.
 */
char* read_sequence(struct Lexer *lex) {
    int position = lex->position;

    while (is_letter(lex->ch) || is_numeric(lex->ch)) {
        next_char(lex);
    }

    int length = lex->position - position;

    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    memcpy(result, lex->input + position, length + 1);

    // The parser will throw an error if token->literal contains both letters and digits
    if (is_letter(result[length]) == false && is_numeric(result[length]) == false) {
        // result == `[x-byte]\0\0`
        result[length] = '\0';
        // Remove the last null terminator
        result = realloc(result, length);

        if (result == NULL) {
            return NULL;
        }
    }

    return result;
}


/**
 * Skips over whitespace characters in the lexer input stream.
 *
 * @param lex A pointer to a lexer objec
 * 
 * @return void
 */
void jump_whitespace(struct Lexer* lex) {
    while (lex->ch == ' ' || lex->ch == '\t' || lex->ch == '\n' || lex->ch == '\r') {
        next_char(lex);
    }
}