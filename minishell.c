#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	char	*prompt;
	t_list	**splited_str;
	while (1)
	{
		prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
		splited_str = lexer(prompt, 0, 0, 0);
		printf("%s\n", (*splited_str)->command);
		printf("%s\n", (*splited_str)->next->command);
		printf("%s\n", (*splited_str)->next->next->command);
		printf("%s\n", (*splited_str)->next->next->next->command);
		printf("%s\n", (*splited_str)->next->next->next->next->command);
		system("leaks a.out");
	}
}
