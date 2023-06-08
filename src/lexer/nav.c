#include <string.h>
#include <stdlib.h>

#include <utils/chardef.h>

#include <lexer/lib.h>

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
void __next_char(struct Lexer* lex) {
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

byte __peek_prev_char(struct Lexer *lexer) {
    if (lexer->read_position >= lexer->input_length) {
        return 0;
    }
    
    return lexer->input[lexer->read_position - 2];
}

byte __peek_next_char(struct Lexer *lexer) {
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
char* __read_sequence(struct Lexer *lex) {
    int position = lex->position;

    while ((is_letter(lex->ch) || is_numeric(lex->ch)) ||
            // signed numbers will match with this condition
           (lex->ch == '-' && is_numeric(__peek_next_char(lex)))) {
                __next_char(lex);
    }

    int length = lex->position - position;

    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    memcpy(result, lex->input + position, length + 1);
    
    result[length] = '\0';

    // if (!is_valid_char_in_sequence(result[length])) {
    //     result[length] = '\0';
    // }

    return result;
}

/**
 * Skips over whitespace characters in the lexer input stream.
 *
 * @param lex A pointer to a lexer objec
 * 
 * @return void
 */
void __jump_whitespace(struct Lexer* lex) {
    while (lex->ch == ' ' || lex->ch == '\t' || lex->ch == '\n' || lex->ch == '\r') {
        __next_char(lex);
    }
}