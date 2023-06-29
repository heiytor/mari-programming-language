#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <ast/lib.h>
#include <lexer/lib.h>
#include <token/lib.h>
#include <parser/lib.h>

#define PROMPT ">>> "

void start(FILE *in, FILE *out) {
    char* line = NULL;
    size_t len = 0;
    __ssize_t read;

    while(1) {
        printf(PROMPT);
        read = getline(&line, &len, in);

        if (read == 1) {
            return;
        }

        struct Lexer *lexer = new_lexer(line);
        struct Token *token = lexer->consume_token(lexer);
        // struct Parser *parser = new_parser(l);
        print_token(token);

        while (token->code != END_OF_FILE) {
            token = lexer->consume_token(lexer);
            print_token(token);
        }

        // parser->parse_program(parser);
    }
}

int main() {
    start(stdin, stdout);

    return 0;
}