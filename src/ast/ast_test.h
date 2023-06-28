#ifndef AST_TEST_H
#define AST_TEST_H

#include <lexer/lib.h>
#include <ast/def.h>

void test_should_pass_if_program_to_string_is_equal_than_input();

void test_should_pass_if_return_statement_to_string_is_equal_than_input();
void test_should_pass_if_mutable_var_statement_to_string_is_equal_than_input();
void test_should_pass_if_var_statement_to_string_is_equal_than_input();

#endif /* AST_TEST_H */