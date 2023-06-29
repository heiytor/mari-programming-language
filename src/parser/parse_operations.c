#include <stdlib.h>

#include <ast/lib.h>
#include <parser/lib.h>


struct Statement* __PARSER_parse_expression_statement(struct Parser* self) {
    struct Statement* expression_statement = (struct Statement*)malloc(sizeof(struct Statement));

    expression_statement->type = 100;
    expression_statement->token = self->curr_token;
    expression_statement->mut = 0;
    expression_statement->to_string = __AST_expression_statement_to_string;
    expression_statement->identifier = NULL;

    // expression_statement->expression = (struct Expression*)malloc(sizeof(struct Expression));

    if (self->next_token_is(self, SEMICOLON)) {
        self->consume_token(self);
    }

    return expression_statement;
}

/**
 * Parses a variable declaration statement from the current and following tokens.
 *
 * This function creates a new variable statement and fills its properties based on 
 * the current and following tokens. Errors are pushed to the parser's error list if 
 * the expected tokens are not found. It keeps consuming tokens until a semicolon is found.
 *
 * @param self The parser object.
 *
 * @return The parsed variable statement, or NULL if an error occurs.
 */
struct Statement* __PARSER_parse_var_statement(struct Parser* self) {
    struct Statement* var_statement = (struct Statement*)malloc(sizeof(struct Statement));

    var_statement->type = VARIABLE;
    var_statement->token = self->curr_token;
    var_statement->mut = 0;
    var_statement->to_string = __AST_var_statement_to_string;

    if (self->consume_or_ignore_if_next_token_is(self, MUTABLE)) {
        var_statement->mut = 1;
    }

    if (!self->consume_or_ignore_if_next_token_is(self, IDENT)) {
        __PARSE_push_error(self, "After \"var\" or \"mut\" keyword, the name of the variable is expected. Line %d, column %d, found: %s.");
        return NULL;
    }

    var_statement->identifier = (struct Identifier*)malloc(sizeof(struct Identifier));
    var_statement->identifier->token = self->curr_token;
    var_statement->identifier->value = self->curr_token->literal;

    if (!self->consume_or_ignore_if_next_token_is(self, ASSIGN)) {
        __PARSE_push_error(self, "After variable name, \"=\" is expected. Line %d, column %d, found: %s.");
        return NULL;
    }

    while (!self->curr_token_is(self, SEMICOLON)) {
        self->consume_token(self);
    }

    return var_statement;
}

/**
 * Parses a return statement from the current and following tokens.
 *
 * This function creates a new return statement and fills its properties based on 
 * the current state of the parser. It keeps consuming tokens until a semicolon is found.
 *
 * @param self The parser object.
 *
 * @return The parsed return statement.
 */
struct Statement* __PARSER_parse_return_statement(struct Parser* self) {
    struct Statement* return_statement = (struct Statement*)malloc(sizeof(struct Statement));

    return_statement->type = RETURN;
    return_statement->identifier = NULL;
    return_statement->token = self->curr_token;
    return_statement->mut = 0;
    return_statement->to_string = __AST_return_statement_to_string;

    self->consume_token(self);

    while (!self->curr_token_is(self, SEMICOLON)) {
        self->consume_token(self);
    }

    return return_statement;
}

/**
 * Parses a statement based on the type of the current token.
 *
 * If the current token represents a variable declaration, it calls the function to 
 * parse variable declarations. If it's a return statement, it calls the function to 
 * parse return statements. Otherwise, it assumes the statement is an expression 
 * statement and calls the function to parse expression statements.
 *
 * @param self The parser object.
 *
 * @return The parsed statement.
 */
struct Statement* __PARSER_parse_statement(struct Parser* self) {
    if (self->curr_token->code == VARIABLE) {
        return self->parse_var_statement(self);
    }

    if (self->curr_token->code == RETURN) {
        return self->parse_return_statement(self);
    }

    return self->parse_expression_statement(self);
}

/**
 * Parses a program, which is a series of statements until the end of file token.
 *
 * This function creates a new program object and continuously parses statements, 
 * adding them to the program, until it reaches the end of file token. It consumes 
 * a token after each statement is parsed.
 *
 * @param self The parser object.
 *
 * @return The parsed program.
 */
struct Program* __PARSER_parse_program(struct Parser* self) {
    struct Program *program = malloc(sizeof(struct Program));

    program->statements_capacity = 10;
    program->statements_size = 0;
    program->statements = malloc(program->statements_capacity * sizeof(struct Statement *));
    program->to_string = __AST_program_to_string;

    while (!self->curr_token_is(self, END_OF_FILE)) {
        struct Statement *statement = self->parse_statement(self);

        if (statement != NULL) {
            __AST_push_statement_to_program(program, statement);
        }

        self->consume_token(self);
    }

    return program;
}
