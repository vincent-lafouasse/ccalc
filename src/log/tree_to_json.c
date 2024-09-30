#include "tree_to_json.h"

#include <stdio.h>

static const char* node_repr(enum e_symbol_kind kind)
{

    if (kind == TERMINAL)
        return "Terminal";
    if (kind == EXPR)
        return "Expr";
    if (kind == EXPR_REST)
        return "Expr'";
    if (kind == TERM)
        return "Term";
    if (kind == TERM_REST)
        return "Term'";
    if (kind == FACTOR)
        return "Factor";
    return "???";
}

void print_terminal(const t_symbol* node);
void print_non_terminal(const t_symbol* node);

void print_node(const t_symbol* node)
{
    if (node->kind == TERMINAL)
        print_terminal(node);
    else
        print_non_terminal(node);
}

void print_terminal(const t_symbol* node)
{
    printf("{");

    printf("text: { name: \"");
    if (node->token.type == INTEGER)
        printf("%d", node->token.value);
    else
        printf("%s", token_repr(node->token));
    printf("\"},");

    printf("children: [],");

    printf("}");
}

void print_non_terminal(const t_symbol* node)
{
    printf("{");

    printf("text: { name: \"%s\" },", node_repr(node->kind));



    printf("children: [");

    for (size_t i = 0; i < node->right_hand_side->len; i++)
    {
        print_node(&node->right_hand_side->data[i]);
        printf(",");
    }

    printf("],");

    printf("}");
}

void tree_to_json(const t_symbol *root)
{
    (void)root;
    printf("parse_tree = {");

    printf("chart: { container: \"#tree-simple\" },");

    printf("nodeStructure: ");

    print_node(root);

    printf("};\n");
}
