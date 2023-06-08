#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <lexer/lib.h>
#include <token/lib.h>


int are_tok_equal(struct Token *t1, struct Token *t2) {
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

void comp_tok(char* input, struct Token expected_tok[], int num_expected_tok, char *test_name) {
    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    int num_tok = 0;

    struct Token *tok;
    for (int i = 0; tok->code != END_OF_FILE; i++) {
        tok = lex->next_token(lex);
        push_token(toks, tok);
        ++num_tok;
    }

    // printf("\n");
    // for (int i = 0; i < num_tok; i++) {
    //     printf("i[%d] ", i);
    //     print_token(toks->tokens[i]);
    // }

    free(lex);

    if (num_tok != num_expected_tok) {
        printf("\x1b[35m%s:\x1b[0m \x1b[31mNumber of tokens mismatch want=%d got=%d.\x1b[0m\n", test_name, num_expected_tok, num_tok);
        pop_tokens(toks);
        exit(1);
    }

    for (int i = 0; i < num_tok; i++) {
        if (!are_tok_equal(toks->tokens[i], &expected_tok[i])) {
            printf("\x1b[35m%s:\x1b[0m \x1b[31mInvalid token[%d] want=%d got=%d.\x1b[0m\n", test_name, i, expected_tok[i].code, toks->tokens[i]->code);
            pop_tokens(toks);
            exit(1);
        }
    }

    printf("\x1b[36m%s:\x1b[0m \x1b[32mPass.\x1b[0m\n", test_name);

    pop_tokens(toks);
}


void test_number_assignment() {
    char* input = "def my_int = 3000;\n"       // int
                  "def my_hex = 0xFF;\n"       // hex
                  "def my_bin = 0b00;\n"       // binary
                  "def my_oct = 0o01;\n"       // octal
                  "def my_flt = 3.14;\n"       // float
                  "def my_int_with_ = 3_00;\n" // int with _
                  "def my_neg_int = -1321;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        // literal | code | line | column
        { "def", 36, 1, 1 },
        { "my_int", 3, 1, 5 },
        { "=", 5, 1, 12 },
        { "3000", 3, 1, 14 },
        { ";", 30, 1, 18 },
        { "def", 36, 2, 2 },
        { "my_hex", 3, 2, 6 },
        { "=", 5, 2, 13 },
        { "0xFF", 3, 2, 15 },
        { ";", 30, 2, 19 },
        { "def", 36, 3, 2 },
        { "my_bin", 3, 3, 6 },
        { "=", 5, 3, 13 },
        { "0b00", 3, 3, 15 },
        { ";", 30, 3, 19 },
        { "def", 36, 4, 2 },
        { "my_oct", 3, 4, 6 },
        { "=", 5, 4, 13 },
        { "0o01", 3, 4, 15 },
        { ";", 30, 4, 19 },
        { "def", 36, 5, 2 },
        { "my_flt", 3, 5, 6 },
        { "=", 5, 5, 13 },
        { "3", 3, 5, 15 },
        { ".", 15, 5, 16 },
        { "14", 3, 5, 17 },
        { ";", 30, 5, 19 },
        { "def", 36, 6, 2 },
        { "my_int_with_", 3, 6, 6 },
        { "=", 5, 6, 19 },
        { "3_00", 3, 6, 21 },
        { ";", 30, 6, 25 },
        { "def", 36, 7, 2 },
        { "my_neg_int", 3, 7, 6 },
        { "=", 5, 7, 17 },
        { "-1321", 3, 7, 19 },
        { ";", 30, 7, 24 },
        { "", 2, 7, 25 },
    };

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_number_assignment");
}

void test_bool_assignment() {
    char* input = "def my_true = true;\n"
                  "def my_false = false;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        // literal | code | line | column
        { "def", 36, 1, 1 },
        { "my_true", 3, 1, 5 },
        { "=", 5, 1, 13 },
        { "true", 41, 1, 15 },
        { ";", 30, 1, 19 },
        { "def", 36, 2, 2 },
        { "my_false", 3, 2, 6 },
        { "=", 5, 2, 15 },
        { "false", 42, 2, 17 },
        { ";", 30, 2, 22 },
        { "", 2, 2, 23 },
    };

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_bool_assignment");
}

// Tests all delimiters at once
void test_delimiters() {
    char *input = "() {};";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        // literal | code | line | column
        { "(", 31, 1, 1 },
        { ")", 32, 1, 2 },
        { "{", 33, 1, 4 },
        { "}", 34, 1, 5 },
        { ";", 30, 1, 6 },
        { "",  2,  1, 7 },
    };

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_delimiters");
}

// Tests all single symbols at once
void test_single_symbol() {
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
        { "",  2,  1, 25 },
    };

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_single_symbol");
}

// Tests all compound symbols at once
void test_compound_symbol() {
    char *input = "++ -- ** !! ==;\n"
                  "+= -= *= /= <= >= !=;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { "++", 16, 1, 1  },
        { "--", 17, 1, 4  },
        { "**", 22, 1, 7  },
        { "!!", 24, 1, 10 },
        { "==", 13, 1, 13 },
        { ";",  30, 1, 15 },
        { "+=", 19, 2, 2  },
        { "-=", 18, 2, 5  },
        { "*=", 20, 2, 8  },
        { "/",  10, 2, 11 },
        { "=",  5, 2, 12  },
        { "<=", 27, 2, 14 },
        { ">=", 28, 2, 17 },
        { "!=", 14, 2, 20 },
        { ";",  30, 2, 22 },
        { "",   2,  2, 23 },
    };

    int num_tok = 0;

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_compound_symbol");
}

// Should pass if ";" don't concatenate with other characters
void test_semicolon_symbol_independence() {
    char* input = ";* ;+ ;- ;= ;> ;<\n"
                  "*; +; -; =; <; >;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { ";", 30, 1, 1  },
        { "*", 9,  1, 2  },
        { ";", 30, 1, 4  },
        { "+", 6,  1, 5  },
        { ";", 30, 1, 7  },
        { "-", 7,  1, 8  },
        { ";", 30, 1, 10 },
        { "=", 5,  1, 11 },
        { ";", 30, 1, 13 },
        { ">", 12, 1, 14 },
        { ";", 30, 1, 16 },
        { "<", 11, 1, 17 },
        { "*", 9,  2, 2  },
        { ";", 30, 2, 3  },
        { "+", 6,  2, 5  },
        { ";", 30, 2, 6  },
        { "-", 7,  2, 8  },
        { ";", 30, 2, 9  },
        { "=", 5,  2, 11 },
        { ";", 30, 2, 12 },
        { "<", 11, 2, 14 },
        { ";", 30, 2, 15 },
        { ">", 12, 2, 17 },
        { ";", 30, 2, 18 },
        { "",  2,  2, 19 },
    };

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_semicolon_symbol_independence");
}

