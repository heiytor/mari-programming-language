#include <stdio.h>
#include <string.h>

#include <langdef.h>
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

struct TokenMap keywords[] = {
    {"func", FUNCTION},
    {"var", VARIABLE},
    {"true", TRUE},
    {"false", FALSE},
    {"if", IF},
    {"elif", ELSE_IF},
    {"else", ELSE},
    {"return", RETURN},
    {"mut", MUTABLE},
    {"as", AS},
    {"returns", RETURNS},
};

uint8 get_ident_code(char* ident) {
    struct TokenMap *kw = keywords;

    while (kw->str) {
        if (strcmp(ident, kw->str) == 0) {
            return kw->token_code;
        }

        ++kw;
    }

    return IDENT;
}

struct TokenMap symbols[] = {
    {"=", ASSIGN},
    {"==", EQUAL},
    {"+", PLUS},
    {"+=", PLUS_ASSIGN},
    {"++", INCREMENT},
    {"-", MINUS},
    {"--", DECREMENT},
    {"-=", MINUS_ASSIGN},
    {"*", ASTERISK},
    {"**", POWER},
    {"*=", ASTERISK_ASSIGN},
    {"!=", NOT_EQUAL},
    {"/", SLASH},
    {"/=", SLASH_ASSIGN},
    {"<", LESS_THAN},
    {"<=", LESS_THAN_EQUAL},
    {">", GREATER_THAN},
    {">=", GREATER_THAN_EQUAL},
    {"!", BANG},
    {"!!", DOUBLE_BANG},
    {"{", L_BRACE},
    {"}", R_BRACE},
    {"(", L_PAREN},
    {")", R_PAREN},
    {";", SEMICOLON},
    {",", COMMA},
    {".", DOT},
    {"?", QUESTION},
    {":", COLON},
    {"%%", MODULO},
    {"\0", END_OF_FILE},
};

uint8 get_symbol_code(char *symbol) {
    struct TokenMap* sy = symbols;

    while (sy->str) {
        if (strcmp(symbol, sy->str) == 0) {
            return sy->token_code;
        }

        ++sy;
    }

    return symbol ? ILLEGAL : END_OF_FILE;
}
