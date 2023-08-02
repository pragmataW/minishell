#include "minishell.h"

t_data	data;

void	free_list(t_list **list, char *prompt)
{
	t_list	*iter;
	t_list	*tmp;

	iter = *list;
	free(prompt);
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
	t_table	**parsed_str;

	init_global(env);
	while (1)
	{
		prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
		splited_str = lexer(prompt, 0, 0, 0);
		expander(splited_str, env);
		parsed_str = parser(splited_str);
		executer(parsed_str, 0, -1);
		add_history(prompt);
		free_list(splited_str, prompt);
	}
}
