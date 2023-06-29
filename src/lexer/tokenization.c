#include <string.h>
#include <stdio.h>

#include <utils/chardef.h>

#include <lexer/lib.h>
#include <token/lib.h>

/**
 * Gets the next token from the lexer.
 *
 * @param lexer The lexer.
 *
 * @return A pointer to the next token.
 */
struct Token *__LEXER_consume_token(struct Lexer* lexer) {
    lexer->jump_whitespace(lexer);

    bool is_char_allowed_for_start = is_allowed_as_first_char(lexer->ch);
    byte curr_char = lexer->ch; // this will help us to get the NUMBER code instead IDENT when necessary
    byte next_char = lexer->peek_next_char(lexer);

        // e.g. 312 | 312542.423
    if ((is_numeric(lexer->ch) && is_char_allowed_for_start) ||
        // e.g my_var | my_var1
        (is_letter(lexer->ch) && is_char_allowed_for_start) ||
        // e.g +312 | -312542.423
        (is_number(lexer->ch, next_char))) {
            char* curr_literal = lexer->read_sequence(lexer);
            uint8 code = is_number(curr_char, next_char) == 1 ? NUMBER : get_ident_code(curr_literal);

            // get correct column value
            int column = lexer->column;
            if (column != 1) {
                column -= strlen(curr_literal);
            }

            return new_token(curr_literal, code, lexer->line, column);
    }

    char compound_literal[3] = {lexer->ch, '\0', '\0'};
    int column = lexer->column;

    if (is_compound_symbol(compound_literal[0], next_char)) {
        compound_literal[1] = next_char;
        lexer->consume_char(lexer);
    }

    uint8 code = get_symbol_code(compound_literal);
    struct Token* token = new_token(compound_literal, code, lexer->line, column);
    
    lexer->consume_char(lexer);

    return token;
}
