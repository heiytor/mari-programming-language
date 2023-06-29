#ifndef TOKEN_TEST_H
#define TOKEN_TEST_H

#include <lexer/lib.h>
#include <token/lib.h>

int tokencmp(struct Token *t1, struct Token *t2);
void are_tokens_equal(char* input, struct Token expected_tok[], int num_expected_tok, char *test_name);

void test_should_pass_if_number_assignment_is_equal_to_expected();
void test_should_pass_if_bool_assignments_are_equal_to_expected();
void test_should_pass_if_delimiters_are_equal_to_expected();
void test_should_pass_if_single_symbols_are_equal_to_expected();
void test_should_pass_if_compound_symbols_are_equal_to_expected();
void test_should_pass_if_semicolon_assingment_are_equal_to_expected();

#endif /* TOKEN_TEST_H */