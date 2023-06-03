#ifndef TOKEN_ACTIONS_TEST_H
#define TOKEN_ACTIONS_TEST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <token/codes.h>
#include <token/structs.h>
#include <token/actions.h>

#include <lexer/actions.h>

int are_tok_equal(struct Token *t1, struct Token *t2);

void comp_tok(char* input, struct Token expected_tok[], int num_expected_tok, char *test_name);

void test_single_symbol_tokenization();
void test_variable_and_function_assignment_tokenization();
void test_delimiters_tokenization();
void test_compound_symbol_tokenization();
void test_semicolon_symbol_independence();
void test_numbers_tokenization();

#endif /* TOKEN_ACTIONS_TEST_H */