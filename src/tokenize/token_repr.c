#include "t_token.h"

#define INTEGER_REPR "int"
#define PLUS_REPR "+"
#define MINUS_REPR "-"
#define TIMES_REPR "x"
#define DIVIDES_REPR "/"
#define LPAREN_REPR "("
#define RPAREN_REPR ")"
#define EOF_TOKEN_REPR "END"

#define UNRECOGNIZED_TOKEN "Bad token"

const char *token_repr(t_token token)
{
    if (token.type == INTEGER)
        return INTEGER_REPR;
    if (token.type == PLUS)
        return PLUS_REPR;
    if (token.type == MINUS)
        return MINUS_REPR;
    if (token.type == TIMES)
        return TIMES_REPR;
    if (token.type == DIVIDES)
        return DIVIDES_REPR;
    if (token.type == LPAREN)
        return LPAREN_REPR;
    if (token.type == RPAREN)
        return RPAREN_REPR;
    if (token.type == EOF_TOKEN)
        return EOF_TOKEN_REPR;
    return (UNRECOGNIZED_TOKEN);
}
