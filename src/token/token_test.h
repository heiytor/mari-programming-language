#ifndef TOKEN_ACTIONS_TEST_H
#define TOKEN_ACTIONS_TEST_H

#include <lexer/lib.h>
#include <token/lib.h>

int are_tok_equal(struct Token *t1, struct Token *t2);

void comp_tok(char* input, struct Token expected_tok[], int num_expected_tok, char *test_name);

void test_number_assignment();
void test_bool_assignment();
void test_delimiters();
void test_single_symbol();
void test_compound_symbol();
void test_semicolon_symbol_independence();

#endif /* TOKEN_ACTIONS_TEST_H */