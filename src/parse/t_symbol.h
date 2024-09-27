#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "tokenize/t_token.h"

typedef struct s_symbol_array t_symbol_array;
t_symbol_array	*symbol_array_with_cap(size_t cap);

typedef enum e_symbol_kind {
	TERMINAL,
	EXPR,
	EXPR_REST,
	TERM,
	TERM_REST,
	FACTOR
} t_symbol_kind;

typedef struct s_symbol {
	// either T or NT,
	// if non terminal: contains right_hand_side and no token
	// if terminal: no right_hand_side and has token
	t_symbol_kind kind;
	union {
		t_symbol_array	*right_hand_side;
		t_token			token;
	};
} t_symbol;

static inline t_symbol symbol_new_non_terminal(t_symbol_kind kind, size_t capacity)
{
	t_symbol_array *arr;

	arr = symbol_array_with_cap(capacity);
	return ((t_symbol){kind, {.right_hand_side = arr}});
}

static inline t_symbol symbol_new_terminal(t_token token)
{
	return ((t_symbol){TERMINAL, {.token = token}});
}

typedef struct s_symbol_array {
	size_t					len;
	size_t					cap;
	struct s_symbol	data[];
} t_symbol_array;

t_symbol_array	*symbol_array_with_cap(size_t cap)
{
	t_symbol_array *new;

	new = malloc(sizeof(*new) + sizeof(*new->data) * cap);
	if (!new)
		return NULL;
	new->len = 0;
	new->cap = cap;
	return new;
}

bool	symbol_array_push(t_symbol_array *this, t_symbol symbol)
{
	if (this->len == this->cap)
		return (false);
	this->data[this->len++] = symbol;
	return true;
}
