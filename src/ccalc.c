#include "tokenize/t_token_list/t_token_list.h"
#include "log/log.h"
#include "parse.h"

#include <stddef.h>
#include <stdio.h>

t_token Token(t_token_type ty)
{
	return (t_token){.type = ty};
}
t_token Integer(int self)
{
	return (t_token){.type = INTEGER, .value = self};
}

int main(void)
{
	t_token_list* tokens = NULL;
	tkl_push_back(&tokens, Token(LPAREN));
	tkl_push_back(&tokens, Integer(42));
	tkl_push_back(&tokens, Token(PLUS));
	tkl_push_back(&tokens, Integer(69));
	tkl_push_back(&tokens, Token(RPAREN));
	tkl_push_back(&tokens, Token(DIVIDES));
	tkl_push_back(&tokens, Integer(0));
	tkl_push_back(&tokens, Token(EOF_TOKEN));

	log_token_list(tokens);

	if (parse(tokens))
		printf("ok\n");
	else
		printf("rip bozo\n");

}
