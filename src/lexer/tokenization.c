#include <string.h>

#include <utils/chardef.h>

#include <lexer/lib.h>
#include <token/lib.h>

/**
 * Gets the next token from the lexer.
 *
 * @param lex The lexer.
 *
 * @return A pointer to the next token.
 */
struct Token *__next_token(struct Lexer *lex) {
    lex->jump_whitespace(lex);

    bool is_char_allowed_for_start = is_allowed_as_first_char(lex->ch);
    byte next_literal = lex->peek_next_char(lex);

        // e.g. 312 | 312542.423
    if ((is_numeric(lex->ch) && is_char_allowed_for_start) ||
        // e.g my_var | my_var1
        (is_letter(lex->ch) && is_char_allowed_for_start) ||
        // e.g +312 | -312542.423
        (is_signed_number(lex->ch, next_literal))) {
            char *curr_literal = lex->read_sequence(lex);
            uint8 code = is_numeric(lex->ch) ? NUMBER : get_ident_code(curr_literal);

            // get correct column value
            int column = lex->column;
            if (column != 1) {
                column -= strlen(curr_literal);
            }

            return new_token(curr_literal, code, lex->line, column);
    }

    char curr_literal[3] = {lex->ch, '\0', '\0'};
    int column = lex->column;

    if (is_compound_symbol(curr_literal[0], next_literal)) {
        curr_literal[1] = next_literal;
        lex->next_char(lex);
    }

    uint8 code = get_symbol_code(curr_literal);
    struct Token *tok = new_token(curr_literal, code, lex->line, column);
    
    lex->next_char(lex);

    return tok;
}
