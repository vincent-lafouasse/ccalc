#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "readline/readline.h"
#include "readline/history.h"

static bool string_empty(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int main(void)
{
	char *line;

	while ((line = readline("$ ")))
	{
		printf("%s\n", line);
		if (!string_empty(line))
			add_history(line);
		free(line);
	}
}
