#pragma once

#include <stdlib.h>
#include "tokenize/t_token.h"

typedef struct s_parse_tree_node t_parse_tree_node;

typedef struct s_node_list {
	struct s_parse_tree_node	*node;
	struct s_node_list			*next;
} t_node_list;

static t_node_list *NodeList(t_parse_tree_node *parse_tree)
{
	t_node_list *node;

	node = malloc(sizeof(*node));
	if (!node) return NULL;
	*node = (t_node_list) {parse_tree, NULL};
	return (node);
}

static t_node_list *nl_push_back(t_node_list **this, t_parse_tree_node *parse_tree)
{
	t_node_list	*last;
	t_node_list	*alloc;

	if (!*this)
	{
		*this = NodeList(parse_tree);
		return *this;
	}
	last = *this;
	while (last->next)
		last = last->next;
	alloc = NodeList(parse_tree);
	if (!alloc) return NULL;
	last->next = alloc;
	return last->next;
}

typedef enum e_parse_tree_kind {
	TERMINAL,
	EXPR,
	EXPR_REST,
	TERM,
	TERM_REST,
	FACTOR
} t_parse_tree_kind;

typedef struct s_parse_tree_node {
	t_parse_tree_kind kind;
	// either T or NT,
	// if non terminal: contains children and no token
	// if terminal: no children and has token
	union {
		t_node_list	*children;
		t_token		tok;
	} data;
} t_parse_tree_node;

static inline t_parse_tree_node *NonTerminal(t_parse_tree_kind kind)
{
	t_parse_tree_node *node;

	node = malloc(sizeof(*node));
	*node = (t_parse_tree_node){kind, {.children = NULL}};
	return (node);
}

static inline t_parse_tree_node *Terminal(t_token tok)
{
	t_parse_tree_node *node;

	node = malloc(sizeof(*node));
	*node = (t_parse_tree_node){TERMINAL, {.tok = tok}};
	return (node);
}
