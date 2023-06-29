#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <lexer/lib.h>
#include <token/lib.h>


int tokencmp(struct Token *f_token, struct Token *s_token) {
    if (strcmp(f_token->literal, s_token->literal) != 0) {
        return 0;
    }
    if (f_token->code != s_token->code) {
        return 0;
    }
    if (f_token->line != s_token->line) {
        return 0;
    }
    if (f_token->column != s_token->column) {
        return 0;
    }

    return 1;
}

void are_tokens_equal(char* input, struct Token expected_tokens[], int number_of_expected_tokens, char *test_name) {
    struct Lexer *lexer = new_lexer(input);
    struct Tokens *tokens = new_tokens_array();

    int number_of_tokens = 0;

    struct Token *tok;
    for (int i = 0; tok->code != END_OF_FILE; i++) {
        tok = lexer->consume_token(lexer);
        push_token(tokens, tok);
        ++number_of_tokens;
    }

    // printf("\n");
    // for (int i = 0; i < number_of_tokens; i++) {
    //     printf("i[%d] ", i);
    //     print_token(tokens->tokens[i]);
    // }

    free(lexer);

    if (number_of_tokens != number_of_expected_tokens) {
        printf("\x1b[35m%s:\x1b[0m \x1b[31mNumber of tokens mismatch want=%d got=%d.\x1b[0m\n", test_name, number_of_expected_tokens, number_of_tokens);
        pop_tokens(tokens);
        exit(1);
    }

    for (int i = 0; i < number_of_tokens; i++) {
        if (!tokencmp(tokens->tokens[i], &expected_tokens[i])) {
            printf("\x1b[35m%s:\x1b[0m \x1b[31mInvalid token[%d] want=%d got=%d.\x1b[0m\n", test_name, i, expected_tokens[i].code, tokens->tokens[i]->code);
            pop_tokens(tokens);
            exit(1);
        }
    }

    printf("\x1b[36m%s:\x1b[0m \x1b[32mPass.\x1b[0m\n", test_name);

    pop_tokens(tokens);
}


void test_should_pass_if_number_assignment_is_equal_to_expected() {
    char* input = "var my_int = 3000;\n"       // int
                  "var my_hex = 0xFF;\n"       // hex
                  "var my_bin = 0b00;\n"       // binary
                  "var my_oct = 0o01;\n"       // octal
                  "var my_flt = 3.14;\n"       // float
                  "var my_int_with_ = 3_00;\n" // int with _
                  "var my_neg_int = -1321;";

    struct Lexer *lexer = new_lexer(input);
    struct Tokens *tokens = new_tokens_array();

    struct Token expected_tokens[] = {
        // literal | code | line | column
        { "var",          36, 1, 1  },
        { "my_int",       3,  1, 5  },
        { "=",            5,  1, 12 },
        { "3000",         4,  1, 14 },
        { ";",            30, 1, 18 },
        { "var",          36, 2, 2  },
        { "my_hex",       3,  2, 6  },
        { "=",            5,  2, 13 },
        { "0xFF",         4,  2, 15 },
        { ";",            30, 2, 19 },
        { "var",          36, 3, 2  },
        { "my_bin",       3,  3, 6  },
        { "=",            5,  3, 13 },
        { "0b00",         4,  3, 15 },
        { ";",            30, 3, 19 },
        { "var",          36, 4, 2  },
        { "my_oct",       3,  4, 6  },
        { "=",            5,  4, 13 },
        { "0o01",         4,  4, 15 },
        { ";",            30, 4, 19 },
        { "var",          36, 5, 2  },
        { "my_flt",       3,  5, 6  },
        { "=",            5,  5, 13 },
        { "3.14",         4,  5, 15 },
        { ";",            30, 5, 19 },
        { "var",          36, 6, 2  },
        { "my_int_with_", 3,  6, 6  },
        { "=",            5,  6, 19 },
        { "3_00",         4,  6, 21 },
        { ";",            30, 6, 25 },
        { "var",          36, 7, 2  },
        { "my_neg_int",   3,  7, 6  },
        { "=",            5, 7, 17  },
        { "-1321",        4, 7, 19  },
        { ";",            30, 7, 24 },
        { "",             2, 7, 25  },
    };

    are_tokens_equal(input, expected_tokens, sizeof(expected_tokens)/sizeof(struct Token), "test_should_pass_if_number_assignment_is_equal_to_expected");
}

void test_should_pass_if_bool_assignments_are_equal_to_expected() {
    char* input = "var my_true = true;\n"
                  "var my_false = false;";

    struct Lexer *lexer = new_lexer(input);
    struct Tokens *tokens = new_tokens_array();

    struct Token expected_tokens[] = {
        // literal | code | line | column
        { "var",      36, 1, 1  },
        { "my_true",  3,  1, 5  },
        { "=",        5,  1, 13 },
        { "true",     41, 1, 15 },
        { ";",        30, 1, 19 },
        { "var",      36, 2, 2  },
        { "my_false", 3,  2, 6  },
        { "=",        5,  2, 15 },
        { "false",    42, 2, 17 },
        { ";",        30, 2, 22 },
        { "",         2,  2, 23 },
    };

    are_tokens_equal(input, expected_tokens, sizeof(expected_tokens)/sizeof(struct Token), "test_should_pass_if_bool_assignments_are_equal_to_expected");
}

// Tests all delimiters at once
void test_should_pass_if_delimiters_are_equal_to_expected() {
    char *input = "() {};";

    struct Lexer *lexer = new_lexer(input);
    struct Tokens *tokens = new_tokens_array();

    struct Token expected_tokens[] = {
        // literal | code | line | column
        { "(", 31, 1, 1 },
        { ")", 32, 1, 2 },
        { "{", 33, 1, 4 },
        { "}", 34, 1, 5 },
        { ";", 30, 1, 6 },
        { "",  2,  1, 7 },
    };

    are_tokens_equal(input, expected_tokens, sizeof(expected_tokens)/sizeof(struct Token), "test_should_pass_if_delimiters_are_equal_to_expected");
}

// Tests all single symbols at once
void test_should_pass_if_single_symbols_are_equal_to_expected() {
    char *input = "+ - * ! = < > / ? : , .;";

    struct Lexer *lexer = new_lexer(input);
    struct Tokens *tokens = new_tokens_array();

    struct Token expected_tokens[] = {
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

    are_tokens_equal(input, expected_tokens, sizeof(expected_tokens)/sizeof(struct Token), "test_should_pass_if_single_symbols_are_equal_to_expected");
}

// Tests all compound symbols at once
void test_should_pass_if_compound_symbols_are_equal_to_expected() {
    char *input = "++ -- ** !! ==;\n"
                  "+= -= *= /= <= >= !=;";

    struct Lexer *lexer = new_lexer(input);
    struct Tokens *tokens = new_tokens_array();

    struct Token expected_tokens[] = {
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

    are_tokens_equal(input, expected_tokens, sizeof(expected_tokens)/sizeof(struct Token), "test_should_pass_if_compound_symbols_are_equal_to_expected");
}

// Should pass if ";" don't concatenate with other characters
void test_should_pass_if_semicolon_assingment_are_equal_to_expected() {
    char* input = ";* ;+ ;- ;= ;> ;<\n"
                  "*; +; -; =; <; >;";

    struct Lexer *lexer = new_lexer(input);
    struct Tokens *tokens = new_tokens_array();

    struct Token expected_tokens[] = {
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

    are_tokens_equal(input, expected_tokens, sizeof(expected_tokens)/sizeof(struct Token), "test_should_pass_if_semicolon_assingment_are_equal_to_expected");
}

