#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
		char **a = lexer(prompt, 0, 0, 0);
		printf("%s\n", a[0]);
		printf("%s\n", a[1]);
		printf("%s\n", a[2]);
		printf("%s\n", a[3]);
		printf("%s\n", a[4]);
		printf("%s\n", a[5]);
		printf("%s\n", a[6]);
		printf("%s\n", a[7]);
		printf("%s\n", a[8]);
		printf("%s\n", a[9]);
	}
}