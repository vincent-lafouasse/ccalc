#include "tokenize/t_token_list/t_token_list.h"
#include "log/log.h"
#include "parse.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "readline/readline.h"
#include "readline/history.h"

t_token Token(t_token_type ty)
{
	return (t_token){.type = ty};
}
t_token Integer(int self)
{
	return (t_token){.type = INTEGER, .value = self};
}

size_t int_len(int n)
{
	char buffer[1000] = {0};

	sprintf(buffer, "%d", n);
	return strlen(buffer);
}

t_token_list* tokenize(const char* in)
{
	t_token_list* out = NULL;
	int value;

	while (*in)
	{
		switch (*in) {
			case ' ':
				break;
			case '+':
				tkl_push_back(&out, Token(PLUS));
				break;
			case '-':
				tkl_push_back(&out, Token(MINUS));
				break;
			case 'x':
				tkl_push_back(&out, Token(TIMES));
				break;
			case '/':
				tkl_push_back(&out, Token(DIVIDES));
				break;
			default:
				value = atoi(in);
				tkl_push_back(&out, Integer(value));
				in += int_len(value);
				continue;
		}
		in++;
	}

	tkl_push_back(&out, Token(EOF_TOKEN));
	return out;
}

#if 0
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
#endif

static bool string_empty(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!isspace(str[i]))
			return (false);
	}
	return (true);
}

int main(void)
{
	char *line;
	t_token_list* tokens;

	while ((line = readline("$ ")))
	{
		if (!string_empty(line))
			add_history(line);
		tokens = tokenize(line);
		log_token_list(tokens);
		if (parse(tokens))
			printf("ok\n");
		else
			printf("rip bozo\n");
		free(line);
		tkl_clear(&tokens);
	}
}
