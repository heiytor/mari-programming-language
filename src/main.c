#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <lexer/lib.h>

#include <token/def.h>
#include <token/lib.h>

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

        struct Lexer *l = new_lexer(line);
        struct Token *t = l->next_token(l);
        print_token(t);

        while (t->code != END_OF_FILE) {
            t = l->next_token(l);
            print_token(t);
        }
    }
}

int main() {
    start(stdin, stdout);
    
    return 0;
}