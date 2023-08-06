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
	data.heredoc = 0;
	data.err = 0;
}

void	main_extra(t_list **splited_str, char *prompt)
{
	char	*last_status;

	add_history(prompt);
	last_status = ft_itoa(data.status);
	set_value("?", last_status);
	command_not_found();
	free(last_status);
	free_list(splited_str, prompt);
	data.heredoc = 0;
}

int	main(int argc, char *argv[], char **env)
{
	char	*prompt;
	t_list	**splited_str;

	(void)argc;
	(void)argv;
	init_global(env);
	printf(CLEAR_TERM);
	printf(RESET_CURSOR);
	signals_control();
	while (1)
	{
		prompt = get_input();
		splited_str = lexer(prompt, 0, 0, 0);
		errors(splited_str, prompt);
		if (data.err == 1)
		{
			data.err = 0;
			free_list(splited_str, prompt);
			continue ;
		}
		expander(splited_str);
		parser(splited_str);
		executer(0, -1);
		main_extra(splited_str, prompt);
	}
}
