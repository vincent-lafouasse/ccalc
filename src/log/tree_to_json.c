#include "tree_to_json.h"

#include <stdio.h>

void tree_to_json(const t_symbol *root)
{
    (void)root;
    printf("parse_tree = {");

    printf("chart: { container: \"#tree-simple\" },");

    printf("nodeStructure: { text: {name: \"root\"} }");

    printf("};");
}
