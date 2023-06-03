#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <lexer/actions.h>

#include <token/structs.h>
#include <token/actions.h>
#include <token/codes.h>


int are_tokens_equal(struct Token *t1, struct Token *t2) {
    if (strcmp(t1->literal, t2->literal) != 0) {
        return 0;
    }
    if (t1->code != t2->code) {
        return 0;
    }
    if (t1->line != t2->line) {
        return 0;
    }
    if (t1->column != t2->column) {
        return 0;
    }

    return 1;
}

void run_test(char* input, struct Token expected_tok[], int num_expected_tok, char *test_name) {
    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    int num_tok = 0;

    for (int i = 0; lex->ch != '\0'; i++) {
        struct Token* token = next_token(lex);
        push_token(toks, token);
        ++num_tok;
    }

    // for (int i = 0; i < num_tok; i++) {
    //     print_token(toks->tokens[i]);
    // }

    free(lex);

    if (num_tok != num_expected_tok) {
        printf("%s: number of tokens mismatch. Expected %d, got %d.\n", test_name, num_expected_tok, num_tok);
        pop_tokens(toks);
        exit(1);
    }

    for (int i = 0; i < num_tok; i++) {
        if (!are_tokens_equal(toks->tokens[i], &expected_tok[i])) {
            printf("\n\x1b[35m%s:\x1b[0m \x1b[31mInvalid token[%d]. Expected code=%d, got code=%d.\x1b[0m\n", test_name, i, expected_tok[i].code, toks->tokens[i]->code);
            pop_tokens(toks);
            exit(1);
        }
    }

    printf("\n\x1b[36m%s:\x1b[0m \x1b[32mPass.\x1b[0m\n", test_name);

    pop_tokens(toks);
}


void test_single_symbol_tokenization() {
    char *input = "+ - * ! = < > / ? : , .;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { "+", 6, 1, 1 },
        { "-", 7, 1, 3 },
        { "*", 9, 1, 5 },
        { "!", 8, 1, 7 },
        { "=", 5, 1, 9 },
        { "<", 11, 1, 11 },
        { ">", 12, 1, 13 },
        { "/", 10, 1, 15 },
        { "?", 25, 1, 17 },
        { ":", 26, 1, 19 },
        { ",", 29, 1, 21 },
        { ".", 15, 1, 23 },
        { ";", 30, 1, 24 },
    };

    run_test(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_single_symbol_tokenization");
}

void test_variable_assignment_tokenization() {
    char* input = "def number = 402942;\n"
                  "def add = fn(x, y) { x + y; }";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { "def", 36, 1, 1 },
        { "number", 3, 1, 5 },
        { "=", 5, 1, 12 },
        { "402942", 4, 1, 14 },
        { ";", 30, 1, 20 },
        { "def", 36, 2, 2 },
        { "add", 3, 2, 6 },
        { "=", 5, 2, 10 },
        { "fn", 35, 2, 12 },
        { "(", 31, 2, 14 },
        { "x", 3, 2, 15 },
        { ",", 29, 2, 16 },
        { "y", 3, 2, 18 },
        { ")", 32, 2, 19 },
        { "{", 33, 2, 21 },
        { "x", 3, 2, 23 },
        { "+", 6, 2, 25 },
        { "y", 3, 2, 27 },
        { ";", 30, 2, 28 },
        { "}", 34, 2, 30 },
    };

    run_test(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_variable_assignment_tokenization");
}

void test_delimiters_tokenization() {
    char *input = "() {};";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { "(", 31, 1, 1 },
        { ")", 32, 1, 2 },
        { "{", 33, 1, 4 },
        { "}", 34, 1, 5 },
        { ";", 30, 1, 6 },
    };

    run_test(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_delimiters_tokenization");
}

void test_compound_symbol_tokenization() {
    char *input = "++ -- ** !! ==;\n"
                  "+= -= *= /= <= >= !=;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { "++", 16, 1, 1 },
        { "--", 17, 1, 4 },
        { "**", 22, 1, 7 },
        { "!!", 24, 1, 10 },
        { "==", 13, 1, 13 },
        { ";", 30, 1, 15 },
        { "+=", 19, 2, 2 },
        { "-=", 18, 2, 5 },
        { "*=", 20, 2, 8 },
        { "/", 10, 2, 11 },
        { "=", 5, 2, 12 },
        { "<=", 27, 2, 14 },
        { ">=", 28, 2, 17 },
        { "!=", 14, 2, 20 },
        { ";", 30, 2, 22 },
    };

    int num_tok = 0;

    run_test(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_compound_symbol_tokenization");
}

void test_semicolon_symbol_independence() {
    char* input = ";* ;+ ;- ;= ;> ;<\n"
                  "*; +; -; =; <; >;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { ";", 30, 1, 1 },
        { "*", 9, 1, 2 },
        { ";", 30, 1, 4 },
        { "+", 6, 1, 5 },
        { ";", 30, 1, 7 },
        { "-", 7, 1, 8 },
        { ";", 30, 1, 10 },
        { "=", 5, 1, 11 },
        { ";", 30, 1, 13 },
        { ">", 12, 1, 14 },
        { ";", 30, 1, 16 },
        { "<", 11, 1, 17 },
        { "*", 9, 2, 2 },
        { ";", 30, 2, 3 },
        { "+", 6, 2, 5 },
        { ";", 30, 2, 6 },
        { "-", 7, 2, 8 },
        { ";", 30, 2, 9 },
        { "=", 5, 2, 11 },
        { ";", 30, 2, 12 },
        { "<", 11, 2, 14 },
        { ";", 30, 2, 15 },
        { ">", 12, 2, 17 },
        { ";", 30, 2, 18 },
    };

    run_test(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_semicolon_symbol_independence");
}