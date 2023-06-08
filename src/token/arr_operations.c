#include <stdlib.h>

#include <token/lib.h>

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