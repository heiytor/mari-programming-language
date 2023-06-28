#ifndef AST_DEFINITION_T
#define AST_DEFINITION_T

#include <token/def.h>

/**
 * Represents an expression in the program.
 *
 * An expression is a syntactic unit that produces a value when evaluated.
 * It can be a literal value, a variable reference, an arithmetic operation,
 * a function call, or other constructs. Expressions are used to compute values
 * and perform operations in programming languages.
 */
struct Expression {
};

/**
 * Represents an identifier in the program.
 *
 * An identifier is a name used to identify a variable, function, or other entities
 * in a program. It is associated with an expression and a token that represents
 * the identifier's value or reference.
 *
 * This `struct Identifier` stores information about the associated expression,
 * the token representing the identifier, and the value of the identifier (if applicable).
 */
struct Identifier {
    /** The expression associated with the identifier. */
    struct Expression *expression;

    /** The token representing the identifier. */
    struct Token *token;

    /** The value of the identifier. */
    char *value;
};

/**
 * Represents a statement in the program.
 *
 * A statement is a syntactic unit that performs an action or declares something.
 * It can be an expression, a variable declaration, a return statement, or other constructs.
 * In programming languages, statements are used to control the flow of execution and
 * manipulate data. They form the building blocks of programs.
 *
 * This `struct Statement` stores information about the type of statement, its mutability,
 * associated token, identifier (if applicable), and expression (if applicable).
 */
struct Statement {
    /** Indicates the type of statement. */
    int type;

    /** Indicates whether the statement is mutable (1) or immutable (0). */
    int mut;

    /** Represents the token associated with the statement. */
    struct Token *token;

    /** Identifier associated with the statement (e.g., variable name). */
    struct Identifier *identifier;

    /** Expression associated with the statement (e.g., value assigned to a variable). */
    struct Expression *expression;

    /**
     * Converts a statement to a string representation.
     * 
     * @param self The statement to convert.
     * 
     * @return The string representation of the variable statement.
     */
    char*(*to_string)(struct Statement *self);
};

/**
 * Represents a program in the source code.
 *
 * A program is the root container that holds all the statements of the program.
 * It serves as the top-level structure that encapsulates the entire code.
 * The `struct Program` maintains an array of statement pointers, along with
 * information about the capacity and current size of the array.
 */
struct Program {
    /** An array of pointers to the statements in the program. */
    struct Statement **statements;

    /** The capacity of the statement array. */
    int statements_capacity;

    /** The current size of the statement array. */
    int statements_size;

    /**
     * Converts a program to a string representation.
     * 
     * @param self The program to convert.
     * 
     * @return The string representation of the program.
     */
    char*(*to_string)(struct Program *self);
};

#endif /* AST_DEFINITION_T */