#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


int	main(int argc, char **argv)
{
	char *line;
	printf("aaa\n");
	while (1)
	{
		line = readline("minishell >");
		add_history(line);
		free(line);
	}
}
