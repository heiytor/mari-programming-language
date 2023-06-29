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
void __LEXER_consume_char(struct Lexer* lex) {
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

byte __LEXER_peek_prev_char(struct Lexer* lexer) {
    if (lexer->read_position >= lexer->input_length) {
        return 0;
    }
    
    return lexer->input[lexer->read_position - 2];
}

byte __LEXER_peek_next_char(struct Lexer* lexer) {
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
char* __LEXER_read_sequence(struct Lexer* lexer) {
    int position = lexer->position;

    while ((is_letter(lexer->ch) || is_numeric(lexer->ch) || lexer->ch == '.') ||
            // signed numbers will match with this condition
           ((lexer->ch == '-' || lexer->ch == '+') && is_numeric(__LEXER_peek_next_char(lexer)))) {
                __LEXER_consume_char(lexer);
    }

    int length = lexer->position - position;

    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    memcpy(result, lexer->input + position, length + 1);
    
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
void __LEXER_jump_whitespace(struct Lexer* lexer) {
    while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r') {
        __LEXER_consume_char(lexer);
    }
}