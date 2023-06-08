#include <stdio.h>

#include <token/lib.h>

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
