#include "tree_to_json.h"

#include <stdio.h>

const char* node_repr(enum e_symbol_kind kind)
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

void print_node(const t_symbol* node)
{
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
