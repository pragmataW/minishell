#include "minishell.h"

void free_list(t_list **list)
{
	t_list	*iter;
	t_list	*tmp;
	
	iter = *list;
	while (iter)
	{
		tmp = iter->next;
		free(iter->command);
		free(iter);
		iter = tmp;
	}
}

int	main(int argc, char *argv[], char **env)
{
	char	*prompt;
	t_list	**splited_str;
	t_list	*iter;

	prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
	while (1)
	{
		splited_str = lexer(prompt, 0, 0, 0);
		iter = *splited_str;
		while (iter)
		{
			printf("%s\n", iter->command);
			iter = iter->next;
		}
		free(prompt);
		free(iter);
		free_list(splited_str);
		prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
	}
}
