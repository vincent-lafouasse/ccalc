#include <stdio.h>
#include "parse/parse.h"
#include "t_parser.h"

t_parser_error	produce_expr(t_parser *state);
t_parser_error	produce_expr_rest(t_parser *state);
t_parser_error	produce_term(t_parser *state);
t_parser_error	produce_term_rest(t_parser *state);
t_parser_error	produce_factor(t_parser *state);

t_parser_error	produce_expr(t_parser *state)
{
	if (produce_term(state).type == OK)
	{
		if (produce_expr_rest(state).type == OK)
		{
			return parser_ok();
		}
	}
	return rip_bozo(state);
}

t_parser_error	produce_expr_rest(t_parser *state)
{
	if (parser_match_terminal(state, PLUS))
	{
		if (produce_term(state).type == OK)
		{
			if (produce_expr_rest(state).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_match_terminal(state, MINUS))
	{
		if (produce_term(state).type == OK)
		{
			if (produce_expr_rest(state).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_matches_one_of(state, (t_token_type[]){EOF_TOKEN, RPAREN}, 2))
	{
		return parser_ok();
	}
	return rip_bozo(state);
}

t_parser_error	produce_term(t_parser *state)
{
	if (produce_factor(state).type == OK)
	{
		if (produce_term_rest(state).type == OK)
		{
			return parser_ok();
		}
	}
	return rip_bozo(state);
}

t_parser_error	produce_term_rest(t_parser *state)
{
	if (parser_match_terminal(state, TIMES))
	{
		if (produce_factor(state).type == OK)
		{
			if (produce_term_rest(state).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_match_terminal(state, DIVIDES))
	{
		if (produce_factor(state).type == OK)
		{
			if (produce_term_rest(state).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_matches_one_of(state, (t_token_type[]){PLUS, MINUS, RPAREN, EOF_TOKEN}, 4))
	{
		return parser_ok();
	}
	return rip_bozo(state);
}

t_parser_error	produce_factor(t_parser *state)
{
	if (parser_match_terminal(state, INTEGER))
		return parser_ok();
	else if (parser_match_terminal(state, LPAREN))
	{
		if (produce_expr(state).type == OK)
		{
			if (parser_match_terminal(state, RPAREN))
				return parser_ok();
		}
	}
	return rip_bozo(state);
}

bool parse(const t_token_list* tokens)
{
	t_parser state = parser_new((t_token_list*)tokens);

	if (produce_expr(&state).type == OK)
	{
		if (parser_matches(&state, EOF_TOKEN))
			return true;
	}
	return false;
}
