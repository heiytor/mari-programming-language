#ifndef PARSER_DEFINITION_H
#define PARSER_DEFINITION_H

#include <ast/def.h>
#include <lexer/def.h>
#include <langdef.h>
#include <token/def.h>

/**
 * Represents a node in a linked list of parser errors.
 *
 * Each node contains a string representing an error message, and a pointer to
 * the next error node in the list. This structure is used to track and report
 * errors that occur during the parsing process.
 */
struct Parser_error {
    /** The error message. */
    char *error;

    /** A pointer to the next error node in the list. */
    struct Parser_error *next;
};

/**
 * Represents a parser.
 *
 * A parser is responsible for transforming a sequence of tokens, produced by a
 * lexer, into an abstract syntax tree (AST). This structure contains a lexer,
 * the current and next tokens being parsed, functions to consume tokens and
 * check token types, and functions to parse different types of statements and
 * the whole program.
 */
struct Parser {
    /** A linked list of error messages produced during the parsing process. */
    struct Parser_error *errors;

    /** The lexer used to produce tokens for the parser. */
    struct Lexer *lexer;

    /** The current token being parsed. */
    struct Token *curr_token;

    /** The next token to be parsed. */
    struct Token *next_token;

    /**
     * Consumes the current token and advances the lexer.
     * 
     * @param self - The Parser object.
     */
    void (*consume_token)(struct Parser *self);

    /**
     * Checks if the next token's code matches the provided code.
     * 
     * @param self - The Parser object.
     * @param code - The code to be compared with the next token's code.
     * 
     * @return 1 if the codes match, 0 otherwise.
     */
    int (*next_token_is)(struct Parser *self, uint8 code);

    /**
     * Checks if the current token's code matches the provided code.
     * 
     * @param self - The Parser object.
     * @param code - The code to be compared with the current token's code.
     * 
     * @return 1 if the codes match, 0 otherwise.
     */
    int (*curr_token_is)(struct Parser *self, uint8 code);

    /**
     * Consumes the next token if its code matches the provided code, or does nothing otherwise.
     * 
     * @param self - The Parser object.
     * @param code - The code to be compared with the next token's code.
     * 
     * @return 1 if the next token was consumed, 0 otherwise.
     */
    int (*consume_or_ignore_if_next_token_is)(struct Parser *self, uint8 code);

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
    struct Program *(*parse_program)(struct Parser *self);

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
    struct Statement *(*parse_statement)(struct Parser *self);

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
    struct Statement *(*parse_var_statement)(struct Parser *self);

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
    struct Statement *(*parse_return_statement)(struct Parser *self);

    struct Statement *(*parse_expression_statement)(struct Parser *self);
};

#endif /* PARSER_DEFINITION_H */
