#include <ast/def.h>

#include <lexer/lib.h>
#include <parser/lib.h>


void __P_next_token(struct Parser *self) {
    self->curr_tok = self->next_tok;
    self->curr_tok = self->lexer->next_token(self->lexer);
}

struct Program *__parse_program(struct Parser *self) {
    return NULL;
}
