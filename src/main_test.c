#include <stdio.h>

#include <ast/ast_test.h>
#include <token/token_test.h>

void print_test_group(char* str) {
    printf("\n\x1b[33m%s:\x1b[0m\n", str);
}

int main() {
    print_test_group("TOKEN");
    test_should_pass_if_number_assignment_is_equal_to_expected();
    test_should_pass_if_bool_assignments_are_equal_to_expected();
    test_should_pass_if_delimiters_are_equal_to_expected();
    test_should_pass_if_single_symbols_are_equal_to_expected();
    test_should_pass_if_compound_symbols_are_equal_to_expected();
    test_should_pass_if_semicolon_assingment_are_equal_to_expected();

    print_test_group("AST");
    test_should_pass_if_return_statement_to_string_is_equal_to_expected();
    test_should_pass_if_var_statement_to_string_is_equal_to_expected();
    test_should_pass_if_mutable_var_statement_to_string_is_equal_to_expected();
    test_should_pass_if_program_to_string_is_equal_to_expected();

    printf("\n\x1b[32mAll tests pass.\x1b[0m\n");

    return 0;
}