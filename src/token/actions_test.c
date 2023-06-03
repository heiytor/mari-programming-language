#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <lexer/actions.h>

#include <token/structs.h>
#include <token/actions.h>
#include <token/codes.h>


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

    for (int i = 0; lex->ch != '\0'; i++) {
        struct Token* token = next_token(lex);
        push_token(toks, token);
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


// Tests all single symbols at once
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

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_single_symbol_tokenization");
}

// Tests all ways to assign functions and variables
void test_variable_and_function_assignment_tokenization() {
    char* input = "def number = 402942;\n"
                  "def add = func(x, y) { x + y; }\n"
                  "def func square(x) {\n"
                  "\treturn x ** 2;\n"
                  "}";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { "def",     code: 36,  line: 1,  column: 1  },
        { "number",  code: 3,   line: 1,  column: 5  },
        { "=",       code: 5,   line: 1,  column: 12 },
        { "402942",  code: 4,   line: 1,  column: 14 },
        { ";",       code: 30,  line: 1,  column: 20 },
        { "def",     code: 36,  line: 2,  column: 2  },
        { "add",     code: 3,   line: 2,  column: 6  },
        { "=",       code: 5,   line: 2,  column: 10 },
        { "func",    code: 35,  line: 2,  column: 12 },
        { "(",       code: 31,  line: 2,  column: 16 },
        { "x",       code: 3,   line: 2,  column: 17 },
        { ",",       code: 29,  line: 2,  column: 18 },
        { "y",       code: 3,   line: 2,  column: 20 },
        { ")",       code: 32,  line: 2,  column: 21 },
        { "{",       code: 33,  line: 2,  column: 23 },
        { "x",       code: 3,   line: 2,  column: 25 },
        { "+",       code: 6,   line: 2,  column: 27 },
        { "y",       code: 3,   line: 2,  column: 29 },
        { ";",       code: 30,  line: 2,  column: 30 },
        { "}",       code: 34,  line: 2,  column: 32 },
        { "def",     code: 36,  line: 3,  column: 2  },
        { "func",    code: 35,  line: 3,  column: 6  },
        { "square",  code: 3,   line: 3,  column: 11 },
        { "(",       code: 31,  line: 3,  column: 17 },
        { "x",       code: 3,   line: 3,  column: 18 },
        { ")",       code: 32,  line: 3,  column: 19 },
        { "{",       code: 33,  line: 3,  column: 21 },
        { "return",  code: 40,  line: 4,  column: 3  },
        { "x",       code: 3,   line: 4,  column: 10 },
        { "**",      code: 22,  line: 4,  column: 12 },
        { "2",       code: 4,   line: 4,  column: 15 },
        { ";",       code: 30,  line: 4,  column: 16 },
        { "}",       code: 34,  line: 5,  column: 2  },
    };

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_variable_and_function_assignment_tokenization");
}

// Tests all delimiters at once
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

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_delimiters_tokenization");
}

// Tests all compound symbols at once
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

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_compound_symbol_tokenization");
}

// Tests all compound symbols at once
// TODO:
//     ADD NEGATIVE SUPPORT
void test_numbers_tokenization() {
    char *input = "0xFF;\n" // hex
                  "0b00;\n" // binary
                  "0o01;\n" // octal
                  "3.14;\n" // float
                  "3000;\n" // int
                  "3_00;";  // int with _

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { "0xFF",  code: 4,   line: 1,  column: 1 },
        { ";",     code: 30,  line: 1,  column: 5 },
        { "0b00",  code: 4,   line: 2,  column: 2 },
        { ";",     code: 30,  line: 2,  column: 6 },
        { "0o01",  code: 4,   line: 3,  column: 2 },
        { ";",     code: 30,  line: 3,  column: 6 },
        { "3.14",  code: 4,   line: 4,  column: 2 },
        { ";",     code: 30,  line: 4,  column: 6 },
        { "3000",  code: 4,   line: 5,  column: 2 },
        { ";",     code: 30,  line: 5,  column: 6 },
        { "3_00",  code: 4,   line: 6,  column: 2 },
        { ";",     code: 30,  line: 6,  column: 6 },
    };

    int num_tok = 0;

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_numbers_tokenization");
}


// Should pass if ";" don't concatenate with other characters
void test_semicolon_symbol_independence() {
    char* input = ";* ;+ ;- ;= ;> ;<\n"
                  "*; +; -; =; <; >;";

    struct Lexer *lex = new_lexer(input);
    struct Tokens *toks = init_token_arr();

    struct Token expected_tok[] = {
        { ";", 30, 1, 1 },
        { "*", 10, 1, 2 },
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

    comp_tok(input, expected_tok, sizeof(expected_tok)/sizeof(struct Token), "test_semicolon_symbol_independence");
}