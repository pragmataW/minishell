#include "minishell.h"

t_data	data;

void	free_list(t_list **list)
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

void	init_global(char **env)
{
	t_env	*envs;

	envs = env_variables(env, 0);
	data.env = envs;
	data.counter = 0;
}

int	main(int argc, char *argv[], char **env)
{
	char	*prompt;
	t_list	**splited_str;
	t_list	*iter;

	init_global(env);
	prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
	while (1)
	{
		splited_str = lexer(prompt, 0, 0, 0);
		expand_cmd(splited_str, data.env, 0);
		expander(splited_str, env);
		iter = *splited_str;
		while (iter)
		{
			printf("%s\n", iter->command);
			iter = iter->next;
		}
		free(iter);
		free(prompt);
		free_list(splited_str);
		prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
	}
}

