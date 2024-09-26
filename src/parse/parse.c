#include <stdio.h>
#include "error/t_error.h"
#include "parse/parse.h"
#include "parse/t_parse_tree.h"
#include "t_parser.h"

t_parse_tree_node	*produce_expr(t_parser *state);
t_parse_tree_node	*produce_expr_rest(t_parser *state);
t_parse_tree_node	*produce_term(t_parser *state);
t_parse_tree_node	*produce_term_rest(t_parser *state);
t_parse_tree_node	*produce_factor(t_parser *state);

void *node_list_clear(void *)
{
	return NULL;
}

void *parse_tree_clear(void *)
{
	return NULL;
}

t_error parse(const t_token_list* tokens)
{
	t_parser state = parser_new(tokens);

	*out = produce_expr(&state, out);
	if (state.err != NO_ERROR)
	{
		return (parse_tree_clear(out), state.err);
	}
	if (!parser_matches(&state, EOF_TOKEN))
	{
		return (parse_tree_clear(out), E_UNEXPECTED_TOKEN);
	}
	return NO_ERROR;
}

t_parse_tree_node	*produce_expr(t_parser *state)
{
	t_parser_error err;
	t_parse_tree_node *out;
	t_parse_tree_node *term;
	t_parse_tree_node *expr_rest;

	out = NonTerminal(EXPR);
	if (!out)
		return NULL;
	term = produce_term(state);
	if (!node_list_push_back(&out->data.children, term))
	{
		parse_tree_clear(out);
		state->err = E_OOM;
		return NULL;
	}
	expr_rest = produce_expr_rest(state, expr_rest);
	if (state->err != NO_ERROR)
	{
		parse_tree_clear(out);
		return NULL;
	}
	if (!node_list_push_back(&out->data.children, expr_rest))
	{
		parse_tree_clear(out);
		state->err = E_OOM;
		return NULL;
	}
	return parser_ok();
}

t_parse_tree_node	*produce_expr_rest(t_parser *state)
{
	t_parser_error err;
	t_parse_tree_node *term;
	t_parse_tree_node *expr_rest;

	if (parser_match_terminal(state, PLUS))
	{
		if (produce_term(state, out).type == OK)
		{
			if (produce_expr_rest(state, out).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_match_terminal(state, MINUS))
	{
		if (produce_term(state, out).type == OK)
		{
			if (produce_expr_rest(state, out).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_matches_one_of(state, (t_token_type[]){EOF_TOKEN, RPAREN}, 2))
	{
		return parser_ok();
	}
	state->err = E_UNEXPECTED_TOKEN
}

t_parse_tree_node	*produce_term(t_parser *state)
{
	if (produce_factor(state, out).type == OK)
	{
		if (produce_term_rest(state, out).type == OK)
		{
			return parser_ok();
		}
	}
	state->err = E_UNEXPECTED_TOKEN
}

t_parse_tree_node	*produce_term_rest(t_parser *state)
{
	if (parser_match_terminal(state, TIMES))
	{
		if (produce_factor(state, out).type == OK)
		{
			if (produce_term_rest(state, out).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_match_terminal(state, DIVIDES))
	{
		if (produce_factor(state, out).type == OK)
		{
			if (produce_term_rest(state, out).type == OK)
			{
				return parser_ok();
			}
		}
	}
	else if (parser_matches_one_of(state, (t_token_type[]){PLUS, MINUS, RPAREN, EOF_TOKEN}, 4))
	{
		return parser_ok();
	}
	state->err = E_UNEXPECTED_TOKEN
}

void *cleanup_propagate(t_parser *state, t_parse_tree_node *out, t_error err)
{
	parse_tree_clear(out);
	if (err != NO_ERROR)
		state->err = err;
	return (NULL);
}

t_parse_tree_node	*produce_factor(t_parser *state)
{
	t_parse_tree_node *out;
	t_parse_tree_node *paren;
	t_parse_tree_node *expr;

	if (parser_matches(state, INTEGER))
	{
		out = Terminal(parser_advance_token(state));
		if (!out)
			state->err = E_OOM;
		return out;
	}
	else if (parser_matches(state, LPAREN))
	{
		out = NonTerminal(FACTOR);
		if (!out)
			return cleanup_propagate(state, out, E_OOM);
		paren = Terminal(parser_advance_token(state));
		if (!paren)
			return cleanup_propagate(state, out, E_OOM);
		if (!node_list_push_back(&out->data.children, paren))
			return cleanup_propagate(state, out, E_OOM);
		expr = produce_expr(state, out);
		if (state->err != NO_ERROR)
			return cleanup_propagate(state, out, NO_ERROR);
		if (!node_list_push_back(&out->data.children, expr))
			return cleanup_propagate(state, out, E_OOM);
		if (parser_matches(state, RPAREN))
		{
			paren = Terminal(parser_advance_token(state));
			if (!paren)
				return cleanup_propagate(state, out, E_OOM);
			if (!node_list_push_back(&out->data.children, paren))
				return cleanup_propagate(state, out, E_OOM);
		return out;
		}
	}
	state->err = E_UNEXPECTED_TOKEN
	return NULL;
}
