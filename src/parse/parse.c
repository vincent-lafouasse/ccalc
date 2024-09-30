/*
	t_symbol out;
	t_symbol paren;
	t_symbol expr;

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
*/
#include <stdio.h>
#include "error/t_error.h"
#include "parse/parse.h"
#include "parse/t_symbol.h"
#include "t_parser.h"

/* productions may or may not return a half-initialized, but always `clear`-able
t_symbol object */
t_symbol	produce_expr(t_parser *state);
t_symbol	produce_expr_rest(t_parser *state);
t_symbol	produce_term(t_parser *state);
t_symbol	produce_term_rest(t_parser *state);
t_symbol	produce_factor(t_parser *state);

void *symbol_clear(t_symbol symbol)
{
	if (symbol.kind == TERMINAL)
		return NULL;
	if (symbol.kind != TERMINAL && symbol.right_hand_side == NULL)
		return NULL;

	return NULL;
}

t_error parse(const t_token_list* tokens)
{
	t_parser state = parser_new(tokens);

	t_symbol root = produce_expr(&state);
	if (state.err != NO_ERROR)
	{
		symbol_clear(root);
		return state.err;
	}
	if (parser_peek_token(&state)->type != EOF_TOKEN)
	{
		symbol_clear(root);
		return E_UNEXPECTED_TOKEN;
	}
	return NO_ERROR;
}

t_symbol	produce_expr(t_parser *state)
{
	t_symbol symbol;

	symbol = symbol_new_non_terminal(EXPR, 2);
	if (symbol.right_hand_side == NULL)
	{
		state->err = E_OOM;
		return symbol;
	}

	if (!parser_produce_push(state, &produce_term, symbol.right_hand_side))
	{
		return symbol;
	}
	if (!parser_produce_push(state, &produce_expr_rest, symbol.right_hand_side))
	{
		return symbol;
	}
	return symbol;
}

t_symbol	produce_expr_rest(t_parser *state)
{
	t_symbol symbol = symbol_new_non_terminal(EXPR_REST, 3);
	if (symbol.right_hand_side == NULL)
	{
		state->err = E_OOM;
		return symbol;
	}

	if (parser_accept_push(state, PLUS, symbol.right_hand_side))
	{
		if (!parser_produce_push(state, &produce_term, symbol.right_hand_side))
			return symbol;
		if (!parser_produce_push(state, &produce_expr_rest, symbol.right_hand_side))
			return symbol;
		return symbol;
	}

	if (parser_accept_push(state, MINUS, symbol.right_hand_side))
	{
		if (!parser_produce_push(state, &produce_term, symbol.right_hand_side))
			return symbol;
		if (!parser_produce_push(state, &produce_expr_rest, symbol.right_hand_side))
			return symbol;
		return symbol;
	}

	if (parser_accept_push(state, EOF_TOKEN, symbol.right_hand_side) ||
		parser_accept_push(state, RPAREN, symbol.right_hand_side))
	{
		return symbol;
	}

	state->err = E_UNEXPECTED_TOKEN;
	return symbol;
}

t_symbol	produce_term(t_parser *state)
{
	t_symbol	symbol;

	symbol = symbol_new_non_terminal(TERM, 2);
	if (symbol.right_hand_side == NULL)
	{
		state->err = E_OOM;
		return symbol;
	}

	if (!parser_produce_push(state, &produce_factor, symbol.right_hand_side))
	{
		return symbol;
	}
	if (!parser_produce_push(state, &produce_term, symbol.right_hand_side))
	{
		return symbol;
	}
	return symbol;
}

t_symbol	produce_term_rest(t_parser *state)
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

t_symbol	produce_factor(t_parser *state)
{
	t_symbol	symbol;

	symbol = symbol_new_non_terminal(FACTOR, 3);
	if (symbol.right_hand_side == NULL)
	{
		state->err = E_OOM;
		return symbol;
	}
	if (parser_accept_push(state, LPAREN, symbol.right_hand_side))
	{
		if (!parser_produce_push(state, produce_expr, symbol.right_hand_side))
			return symbol;
		if (!parser_accept_push(state, RPAREN, symbol.right_hand_side))
		{
			state->err = E_UNEXPECTED_TOKEN;
			return symbol;
		}
		return symbol;
	}
	if (parser_accept_push(state, INTEGER, symbol.right_hand_side))
		return symbol;
	state->err = E_UNEXPECTED_TOKEN;
	return symbol;
}
