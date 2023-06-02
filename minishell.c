#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
		printf("%d", word_count(prompt, 0, 0, 0));
	}
}