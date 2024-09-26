#pragma once

typedef enum e_token_type
{
    INTEGER,
    PLUS,
    MINUS,
    TIMES,
    DIVIDES,
    LPAREN,
    RPAREN,
    EOF_TOKEN,
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    int value;
} t_token;

const char *token_repr(t_token token);
