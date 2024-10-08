#include "t_parser.h"
#include "tokenize/t_token.h"
#include <stdbool.h>
#include <stddef.h>

t_parser parser_new(const t_token_list *tokens)
{
    return (
        (t_parser){._head = tokens, .current_token = tokens, .err = NO_ERROR});
}

bool parser_matches(const t_parser *parser, t_token_type type)
{
    return (parser_peek_token(parser)->type == type);
}

bool parser_matches_one_of(const t_parser *parser, const t_token_type types[],
                           size_t type_count)
{
    size_t i;

    i = 0;
    while (i < type_count)
    {
        if (parser_matches(parser, types[i]))
            return (true);
        i++;
    }
    return (false);
}

__attribute__((warn_unused_result)) bool
parser_produce_push(t_parser *parser, t_symbol (*prod)(t_parser *),
                    t_symbol_array *out)
{
    t_symbol symbol;

    symbol = prod(parser);
    symbol_array_push(out, symbol);
    return (parser->err == NO_ERROR);
}

__attribute__((warn_unused_result)) bool
parser_accept_push(t_parser *parser, t_token_type type, t_symbol_array *out)
{
    bool matches;
    t_symbol symbol;

    matches = parser_matches(parser, type);
    if (!matches)
        return false;
    symbol = symbol_new_terminal(parser_advance_token(parser));
    symbol_array_push(out, symbol);
    return true;
}

const t_token *parser_peek_token(const t_parser *parser)
{
    return (&parser->current_token->token);
}

t_token parser_advance_token(t_parser *parser)
{
    t_token token;

    token = parser->current_token->token;
    if (token.type != EOF_TOKEN)
        parser->current_token = parser->current_token->next;
    // TODO: clear node either here or at the top of parse
    return (token);
}
