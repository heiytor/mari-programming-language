#include <stdio.h>

#include <token/token_test.h>

int main() {
    test_number_assignment();
    test_bool_assignment();
    test_delimiters();
    test_single_symbol();
    test_compound_symbol();
    test_semicolon_symbol_independence();

    printf("\n\x1b[32mAll tests pass.\x1b[0m\n");

    return 0;
}