#include <stdlib.h>

#include <ast/lib.h>

/**
 * Pushes a new statement onto the program's statement array. If the capacity of the array is reached,
 * it doubles its size.
 * 
 * @param program - The Program object.
 * @param statement - The statement to be added to the Program object.
 */
void __AST_push_statement_to_program(struct Program *program, struct Statement *statement) {
    if (program->statements_size == program->statements_capacity) {
        program->statements_capacity *= 2;
        program->statements = (struct Statement **)realloc(program->statements,
                                                           program->statements_capacity * sizeof(struct Statement *));
    }

    program->statements[program->statements_size] = statement;
    program->statements_size++;
}

/**
 * Cleans up memory allocated for the program's statements.
 * 
 * @param program - The Program object.
 */
void __AST_pop_program_statements(struct Program *program) {
    for (size_t i = 0; i < program->statements_size; i++) {
        free(program->statements[i]);
    }

    free(program->statements);
    free(program);
}
