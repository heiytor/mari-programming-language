#ifndef AST_LIB_T
#define AST_LIB_T

#include <ast/def.h>
#include <token/def.h>

char* __AST_program_to_string(struct Program *program);
char* __AST_expression_statement_to_string(struct Statement *statement);
char* __AST_var_statement_to_string(struct Statement *statement);
char* __AST_return_statement_to_string(struct Statement *statement);

#endif /* AST_LIB_T */