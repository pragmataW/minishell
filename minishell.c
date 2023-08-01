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
	t_table	*iter;
	t_table	**root;
	int		i;

	init_global(env);
	prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
	add_history(prompt);
	while (1)
	{
		splited_str = lexer(prompt, 0, 0, 0);
		expander(splited_str, env);
		root = parser(splited_str);
        executer(root, 0, 0);
		// iter = *root;
		// while (iter)
		// {
		// 	i = 0;
		// 	printf("cmd_path: %s\n", iter->cmd_path);
		// 	while (iter->full_cmd[i] != NULL)
		// 	{
		// 		printf("full_cmd[%d]: %s\n", i, iter->full_cmd[i]);
		// 		i++;
		// 	}
		// 	printf("infile: %d\n", iter->infile);
		// 	printf("outfile: %d\n", iter->outfile);
		// 	iter = iter->next;
		// }
		// free(prompt);
		//free(iter);
		free_list(splited_str);
		prompt = readline("\033[1;31myciftci🥵minishell->\033[0m");
		add_history(prompt);
	}
}
