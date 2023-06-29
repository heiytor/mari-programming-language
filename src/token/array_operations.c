#include <stdlib.h>

#include <token/lib.h>

/**
 * Initializes a dynamic array of tokens.
 *
 * @return A pointer to the newly created token array.
 */
struct Tokens *new_tokens_array() {
    struct Tokens *tokens_array = (struct Tokens *)malloc(sizeof(struct Tokens));

    tokens_array->capacity = 10;
    tokens_array->size = 0;
    tokens_array->tokens = (struct Token **)malloc(tokens_array->capacity * sizeof(struct Token *));

    return tokens_array;
}

/**
 * Pushes a token to a dynamic array of tokens.
 *
 * @param array The token array.
 * @param token The token to be added.
 */
void push_token(struct Tokens *array, struct Token *token) {
    if (array->size == array->capacity) {
        array->capacity *= 2;
        array->tokens = (struct Token **)realloc(array->tokens,
                                                 array->capacity * sizeof(struct Token *));
    }

    array->tokens[array->size] = token;
    array->size++;
}

/**
 * Deallocates the memory used by the token array and all its tokens.
 *
 * @param array The token array to be deallocated.
 */
void pop_tokens(struct Tokens *array) {
    for (size_t i = 0; i < array->size; i++) {
        free(array->tokens[i]);
    }

    free(array->tokens);
    free(array);
}