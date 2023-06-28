#ifndef AST_LIB_T
#define AST_LIB_T

#include <ast/def.h>
#include <token/def.h>

void __AST_push_statement_to_program(struct Program* program, struct Statement* statement);
void __AST_pop_program_statements(struct Program* program);

char* __AST_program_to_string(struct Program *program);
char* __AST_expression_statement_to_string(struct Statement *statement);
char* __AST_var_statement_to_string(struct Statement *statement);
char* __AST_return_statement_to_string(struct Statement *statement);

#endif /* AST_LIB_T */