#include "t_symbol.h"

#include <stdlib.h>

t_symbol symbol_new_non_terminal(t_symbol_kind kind, size_t capacity)
{
    t_symbol_array *arr;

    arr = symbol_array_with_cap(capacity);
    return ((t_symbol){kind, {.right_hand_side = arr}});
}

t_symbol symbol_new_terminal(t_token token)
{
    return ((t_symbol){TERMINAL, {.token = token}});
}

t_symbol_array *symbol_array_with_cap(size_t cap)
{
    t_symbol_array *new;

    new = malloc(sizeof(*new) + sizeof(*new->data) * cap);
    if (!new)
        return NULL;
    new->len = 0;
    new->cap = cap;
    return new;
}

bool symbol_array_push(t_symbol_array *this, t_symbol symbol)
{
    if (this->len == this->cap)
        return (false);
    this->data[this->len++] = symbol;
    return true;
}
