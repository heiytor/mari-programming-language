#ifndef LEXER_DEF_H
#define LEXER_DEF_H

#include <langdef.h>
#include <token/def.h>

struct Lexer {
    char* input;
    int   input_length;
    int   position;
    int   read_position;
    byte  ch;
    int   line;
    int   column;

    void  (*consume_char)(struct Lexer *self);
    char *(*read_sequence)(struct Lexer *self);
    void  (*jump_whitespace)(struct Lexer *self);
    byte  (*peek_prev_char)(struct Lexer *self);
    byte  (*peek_next_char)(struct Lexer *self);

    struct Token *(*consume_token)(struct Lexer *lex);
};

#endif /* LEXER_DEF_H */