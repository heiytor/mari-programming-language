#include <stdlib.h>
#include <string.h>

#include <ast/lib.h>

/**
 * Converts a program to a string representation.
 * 
 * @param prg The program to convert.
 * 
 * @return The string representation of the program.
 */
char* __AST_program_to_string(struct Program* prg) {
    char* out = strdup("");
    if (out == NULL) return NULL;

    for (int i = 0; i < prg->statements_size; i++) {
        char* statement_string = prg->statements[i]->to_string(prg->statements[i]);
        if (statement_string == NULL) {
            free(out);
            return NULL;
        }

        char* temp = realloc(out, (strlen(out) + strlen(statement_string) + 1) * sizeof(char));
        if (temp == NULL) {
            free(out);
            free(statement_string);
            return NULL;
        }

        out = temp;
        
        strcat(out, statement_string);
        free(statement_string);
    }

    // remove '\n' from at the end of the string
    out[strlen(out) - 1] = '\0';

    return out;
}

/**
 * Converts an expression statement to a string representation.
 *
 * @param stmt The expression statement to convert.
 * 
 * @return The string representation of the expression statement.
 */
char* __AST_expression_statement_to_string(struct Statement* stmt) {
    if (stmt->expression != NULL) {
        // ...
    }

    char* out = '\0';
    return out;
}

/**
 * Converts a return statement to a string representation.
 *
 * @param stmt The return statement to convert.
 * 
 * @return The string representation of the return statement.
 */
char* __AST_return_statement_to_string(struct Statement* stmt) {
    char* out = malloc(sizeof(char));
    out[0] = '\0';

    // Allocate memory for "return " to be stored in temp
    char* temp = realloc(out,
        (strlen(stmt->token->literal) + strlen(" ") + strlen(";") + strlen("\n") + 1) * sizeof(char)
    );

    if (temp == NULL) {
        free(out);
        return NULL;
    }

    out = temp;

    strcpy(out, stmt->token->literal); // "return"
    strcat(out, " "); // "return "

    if (stmt->expression != NULL) {
        // ...
    }

    strcat(out, ";");
    strcat(out, "\n");
    // At the end of this call, temp will look something like: "return {expr};\n"
    return out;
}

/**
 * Converts a variable statement to a string representation.
 *
 * @param stmt The variable statement to convert.
 * 
 * @return The string representation of the variable statement.
 */
char* __AST_var_statement_to_string(struct Statement* stmt) {
    char* out = malloc(sizeof(char));
    out[0] = '\0';

    // Calculate the required length for the output string
    int out_length = strlen(stmt->token->literal) + strlen(" ");

    if (stmt->mut == 1) {
        out_length += strlen("mut ");
    }

    out_length += strlen(stmt->identifier->value) + strlen(" = ");

    char* temp = realloc(out, (out_length + strlen(";") + strlen("\n") + 1) * sizeof(char));
    if (temp == NULL) {
        free(out);
        return NULL;
    }

    out = temp;

    strcpy(out, stmt->token->literal); // "var"
    strcat(out, stmt->mut == 0 ? " " : " mut "); // "var "  || "var mut "
    strcat(out, stmt->identifier->value); // "var {ident}"
    strcat(out, " = "); // "var {ident} = "

    if (stmt->expression != NULL) {
        // ...
    }

    strcat(out, ";");
    strcat(out, "\n");
    // At the end of this call, temp will look something like: "var {ident} = {expr};\n"
    return out;
}
