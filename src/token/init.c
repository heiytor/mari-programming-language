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
