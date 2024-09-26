#pragma once

#include "tokenize/t_token.h"

typedef struct s_node_list {
	struct s_parse_tree_node	*node;
	struct s_node_list			*next;
} t_node_list;

typedef struct s_parse_tree_node {
	enum e_parse_tree_kind {
		TERMINAL,
		EXPR,
		EXPR_REST,
		TERM,
		TERM_REST,
		FACTOR
	} kind;
	// either T or NT,
	// if non terminal: contains children and no token
	// if terminal: no children and has token
	union {
		t_node_list	*children;
		t_token		tok;
	} data;
} t_parse_tree_node;
