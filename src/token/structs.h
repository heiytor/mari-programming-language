#ifndef TOKEN_STRUCTS_H
#define TOKEN_STRUCTS_H

#include <types.h>

struct Token {
    char *literal;
    uint8 code;
    int line;
    int column;
};

struct Tokens {
    struct Token **tokens;
    size_t size;
    size_t capacity;
};

struct Token_Map {
    char *str;
    uint8 token_code;
};

#endif /* TOKEN_STRUCTS_H */