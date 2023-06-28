#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <ast/ast_test.h>
#include <lexer/lib.h>
#include <parser/lib.h>

struct Program* create_program(char* input) {
    struct Lexer* lex = new_lexer(input);
    struct Parser* psr = new_parser(lex);
    struct Program* prg = psr->parse_program(psr);

    return prg;
}

void test_statement(char* want, char* got, char* test_name) {
    int is_equal = strcmp(got, want);

    if (is_equal != 0) {
        printf("\x1b[35m%s:\x1b[0m \x1b[31mInvalid program want=[%s] got=[%s].\x1b[0m\n", test_name, want, got);
        exit(1);
    }

    printf("\x1b[36m%s:\x1b[0m \x1b[32mPass.\x1b[0m\n", test_name);
}

void test_should_pass_if_program_to_string_is_equal_than_input() {
    char* input = "var x = ;\n" // var statement
                  "var mut y = ;\n" // mutable var statement
                  "return ;"; // return statement

    struct Program* prg = create_program(input);

    char* want = "var x = ;\n"
                 "var mut y = ;\n"
                 "return ;";
    char* got = prg->to_string(prg);

    test_statement(want, got, "test_should_pass_if_program_to_string_is_equal_than_input");
}

void test_should_pass_if_return_statement_to_string_is_equal_than_input() {
    char* input = "return ;";
    struct Program* prg = create_program(input);

    // Due to the string handling limitation, 
    // we must include the newline character at the end of the 'want' string.
    char* want = "return ;\n";  
    char* got = prg->statements[0]->to_string(prg->statements[0]);

    test_statement(want, got, "test_should_pass_if_return_statement_to_string_is_equal_than_input");
}

void test_should_pass_if_var_statement_to_string_is_equal_than_input() {
    char* input = "var x = ;";
    struct Program* prg = create_program(input);

    // Due to the string handling limitation, 
    // we must include the newline character at the end of the 'want' string.
    char* want = "var x = ;\n";
    char* got = prg->statements[0]->to_string(prg->statements[0]);

    test_statement(want, got, "test_should_pass_if_var_statement_to_string_is_equal_than_input");
}

void test_should_pass_if_mutable_var_statement_to_string_is_equal_than_input() {
    char* input = "var mut x = ;";
    struct Program* prg = create_program(input);

    // Due to the string handling limitation, 
    // we must include the newline character at the end of the 'want' string.
    char* want = "var mut x = ;\n";
    char* got = prg->statements[0]->to_string(prg->statements[0]);

    test_statement(want, got, "test_should_pass_if_mutable_var_statement_to_string_is_equal_than_input");
}