#include <stdlib.h>

#include <lexer/lib.h>
#include <parser/lib.h>

struct Parser *new_parser(struct Lexer *lexer) {
    struct Parser *parser = malloc(sizeof(struct Parser));

    if (!parser) {
        return NULL;
    }

    parser->lexer = lexer;
    parser->next_token = __P_next_token;

    parser->next_token(parser);
    parser->next_token(parser);    

    return parser;
}