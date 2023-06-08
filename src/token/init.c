#include <stdlib.h>
#include <string.h>

#include <langdef.h>

#include <token/lib.h>

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
    token->literal = strdup(literal); // deep copy
    token->line = line;
    token->column = column;

    return token;
}

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
