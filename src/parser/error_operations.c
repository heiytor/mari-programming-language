#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <parser/lib.h>

/**
 * This function generates an error message and adds it to the parser's error list.
 * The template string should contain placeholders for line, column, and literal in that order.
 * Memory allocated for the error message is automatically freed.
 * Example: `__PARSER_push_error(parser, "Error at line %d, column %d. Found: %s.");`
 * 
 * @param self - The Parser object.
 * @param template - The template string for the error message.
 */
void __PARSE_push_error(struct Parser *self, char *template) {
    int error_lenght = snprintf(NULL, 0, template, self->curr_token->line, self->curr_token->column, self->curr_token->literal);
    char *error = malloc(error_lenght + 1);
    sprintf(error, template, self->curr_token->line, self->curr_token->column, self->curr_token->literal);
    
    struct Parser_error *error_node = malloc(sizeof(struct Parser_error));
    error_node->error = strdup(error);
    error_node->next = self->errors;
    self->errors = error_node;

    free(error);
}

void __PARSE_print_error(struct Parser *self) {
    struct Parser_error *current = self->errors;

    while (current != NULL) {
        printf("Error: %s\n", current->error);
        current = current->next;
    }
}