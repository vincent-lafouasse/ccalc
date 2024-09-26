#include "log.h"

#include <stdio.h>

void log_token(t_token token)
{
    if (token.type == INTEGER)
        printf("%i", token.value);
    else
        printf("%s", token_repr(token));
}

void log_token_list(const t_token_list *tkl)
{
    while (tkl)
    {
        log_token(tkl->token);
        printf(" ");
        tkl = tkl->next;
    }
    printf("\n");
}

void log_error(t_error err)
{
    if (err == NO_ERROR)
    {
        printf("No error\n");
        return;
    }
    printf("Error:\t%s\n", error_repr(err));
}
