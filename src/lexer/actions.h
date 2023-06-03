#ifndef LEXER_METHODS_H
#define LEXER_METHODS_H

#include <types.h>

struct Lexer {
    char* input;
    int input_length;
    int position;
    int read_position;
    byte ch;
    int line;
    int column;
};

void next_char(struct Lexer* lex);

char* read_sequence(struct Lexer* lex);

char* read_identifier(struct Lexer* lex);

void jump_whitespace(struct Lexer* lex);

byte peek_next_char(struct Lexer *lex);

struct Lexer* new_lexer(char* input);

#endif /* LEXER_METHODS_H */