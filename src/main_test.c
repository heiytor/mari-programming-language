#include <stdio.h>

#include <token/actions_test.h>

int main() {
    test_variable_assignment_tokenization();
    test_delimiters_tokenization();
    test_single_symbol_tokenization();
    test_compound_symbol_tokenization();
    test_semicolon_symbol_independence();

    printf("\n\x1b[32mAll tests pass.\x1b[0m\n");

    return 0;
}