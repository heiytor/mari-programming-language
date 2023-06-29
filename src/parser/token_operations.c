#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <langdef.h>

#include <token/def.h>

#include <ast/lib.h>
#include <lexer/lib.h>
#include <parser/lib.h>
#include <token/lib.h>

/**
 * Consumes the current token and advances the lexer.
 * 
 * @param self - The Parser object.
 */
void __PARSER_consume_token(struct Parser *self) {
    self->curr_token = self->next_token;
    self->next_token = self->lexer->next_token(self->lexer);
}

/**
 * Checks if the current token's code matches the provided code.
 * 
 * @param self - The Parser object.
 * @param code - The code to be compared with the current token's code.
 * 
 * @return 1 if the codes match, 0 otherwise.
 */
int __PARSER_curr_token_is(struct Parser *self, uint8 code) {
    return self->curr_token->code == code;
}

/**
 * Checks if the next token's code matches the provided code.
 * 
 * @param self - The Parser object.
 * @param code - The code to be compared with the next token's code.
 * 
 * @return 1 if the codes match, 0 otherwise.
 */
int __PARSER_next_token_is(struct Parser *self, uint8 code) {
    return self->next_token->code == code;
}

/**
 * Consumes the next token if its code matches the provided code, or does nothing otherwise.
 * 
 * @param self - The Parser object.
 * @param code - The code to be compared with the next token's code.
 * 
 * @return 1 if the next token was consumed, 0 otherwise.
 */
int __PARSER_consume_or_ignore_if_next_token_is(struct Parser *self, uint8 code) {
    if (__PARSER_next_token_is(self, code)) {
        self->consume_token(self);
        return 1;
    }

    return 0;
}