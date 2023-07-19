#ifndef LEXER_DEF_H
#define LEXER_DEF_H

#include <langdef.h>
#include <token/def.h>

typedef struct Lexer Lexer;
struct Lexer {
    char*     input;
    int       input_length;
    chcode_t  ch;
    int       position;
    int       read_position;
    int       line;
    int       column;

    void      (*consume_char)(Lexer *self);
    char     *(*read_sequence)(Lexer *self);
    void      (*jump_whitespace)(Lexer *self);
    chcode_t  (*peek_next_char)(Lexer *self);

    Token    *(*consume_token)(Lexer *lex);
};

#endif /* LEXER_DEF_H */