#include <stdlib.h>

#include <lexer/lib.h>
#include <parser/lib.h>
#include <token/lib.h>

struct Parser *new_parser(struct Lexer *lexer) {
    struct Parser *parser = malloc(sizeof(struct Parser));

    if (!parser) {
        return NULL;
    }

    parser->lexer = lexer;

    parser->consume_token = __PARSER_consume_token;
    parser->next_token_is = __PARSER_next_token_is;
    parser->curr_token_is = __PARSER_curr_token_is;
    parser->consume_or_ignore_if_next_token_is = __PARSER_consume_or_ignore_if_next_token_is;
    
    parser->parse_statement = __PARSER_parse_statement;
    parser->parse_program = __PARSER_parse_program;
    parser->parse_var_statement = __PARSER_parse_var_statement;
    parser->parse_return_statement = __PARSER_parse_return_statement;
    parser->parse_expression_statement = __PARSER_parse_expression_statement;

    // We need to advance two tokens to set both parser->curr_token and parser->next_token
    parser->consume_token(parser);
    parser->consume_token(parser);

    return parser;
}