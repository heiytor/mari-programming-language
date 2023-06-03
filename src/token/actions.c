#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <token/codes.h>
#include <types.h>

#include <helpers/characters.h>

#include <token/mappers.h>
#include <token/actions.h>
#include <token/structs.h>

/**
 * Print a token to console.
 *
 * @param tok A pointer to the token.
 */
void print_token(struct Token *tok) {
    printf("{ literal: `%s`, code: %d, line: %d, column: %d }\n",
            tok->literal,
            tok->code,
            tok->line,
            tok->column);

    return;
}

/**
 * Creates a new token with the given literal, code, line, and column.
 *
 * @param literal The literal value of the token.
 * @param code The code of the token.
 * @param line The line number where the token was found.
 * @param column The column number where the token was found.
 *
 * @return A pointer to the newly created token.
 */
struct Token *new_token(char *literal, byte code, int line, int column) {
    struct Token *token = (struct Token*)malloc(sizeof(struct Token));

    token->code = code;
    token->literal = strdup(literal);
    token->line = line;
    token->column = column;

    return token;
}

/**
 * Gets the next token from the lexer.
 *
 * @param lex The lexer.
 *
 * @return A pointer to the next token.
 */
struct Token *next_token(struct Lexer *lex) {
    jump_whitespace(lex);

    if (is_letter(lex->ch)) {
        char *curr_literal = read_sequence(lex);
        uint8 code = map_ident(curr_literal);
        int column = lex->column - strlen(curr_literal);

        return new_token(curr_literal, code, lex->line, column);
    }

    if (is_numeric(lex->ch)) {
        char *curr_literal = read_sequence(lex);
        int column = lex->column - strlen(curr_literal);

        return new_token(curr_literal, INT, lex->line, column);
    }

    char curr_literal[3] = {lex->ch, '\0', '\0'};
    byte next_literal = peek_next_char(lex);
    int column = lex->column;

    if (is_compound_symbol(curr_literal[0], next_literal)) {
        curr_literal[1] = next_literal;
        next_char(lex);
    }

    uint8 code = map_symbol(curr_literal);
    struct Token *tok = new_token(curr_literal, code, lex->line, column);
    
    next_char(lex);

    return tok;
}

// Array

/**
 * Initializes a dynamic array of tokens.
 *
 * @return A pointer to the newly created token array.
 */
struct Tokens *init_token_arr() {
    struct Tokens *tokens_array = (struct Tokens *)malloc(sizeof(struct Tokens));

    tokens_array->capacity = 10;
    tokens_array->size = 0;
    tokens_array->tokens = (struct Token **)malloc(tokens_array->capacity * sizeof(struct Token *));

    return tokens_array;
}

/**
 * Pushes a token to a dynamic array of tokens.
 *
 * @param tok_arr The token array.
 * @param tok The token to be added.
 */
void push_token(struct Tokens *tok_arr, struct Token *tok) {
    if (tok_arr->size == tok_arr->capacity) {
        tok_arr->capacity *= 2;
        tok_arr->tokens = (struct Token **)realloc(tok_arr->tokens,
                                                   tok_arr->capacity * sizeof(struct Token *));
    }

    tok_arr->tokens[tok_arr->size] = tok;
    tok_arr->size++;
}

/**
 * Deallocates the memory used by the token array and all its tokens.
 *
 * @param tok_arr The token array to be deallocated.
 */
void pop_tokens(struct Tokens *tok_arr) {
    for (size_t i = 0; i < tok_arr->size; i++) {
        free(tok_arr->tokens[i]);
    }

    free(tok_arr->tokens);
    free(tok_arr);
}
