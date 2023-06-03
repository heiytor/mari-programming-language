#ifndef INTERPRETER_TOKEN_TYPES_H
#define INTERPRETER_TOKEN_TYPES_H

#define ILLEGAL 1
#define END_OF_FILE 2

#define IDENT 3
#define NUMBER 4

// Operators
#define ASSIGN 5
#define PLUS 6
#define MINUS 7
#define BANG 8
#define ASTERISK 9
#define SLASH 10
#define LESS_THAN 11
#define GREATER_THAN 12
#define EQUAL 13
#define NOT_EQUAL 14
#define DOT 15
#define INCREMENT 16
#define DECREMENT 17
#define MINUS_ASSIGN 18
#define PLUS_ASSIGN 19
#define ASTERISK_ASSIGN 20
#define SLASH_ASSIGN 21
#define POWER 22
#define MODULO 23
#define DOUBLE_BANG 24
#define QUESTION 25
#define COLON 26
#define LESS_THAN_EQUAL 27
#define GREATER_THAN_EQUAL 28

// Delimiters
#define COMMA 29
#define SEMICOLON 30
#define L_PAREN 31
#define R_PAREN 32
#define L_BRACE 33
#define R_BRACE 34

// Keywords
#define FUNCTION 35
#define VARIABLE 36
#define IF 37
#define ELSE_IF 38
#define ELSE 39
#define RETURN 40
#define TRUE 41
#define FALSE 42
#define MUTABLE 43

#endif /* INTERPRETER_TOKEN_TYPES_H */
