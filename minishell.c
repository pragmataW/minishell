#include "minishell.h"

t_data	g_data;

void	init_global(char **env)
{
	t_env	*envs;
	char	*last_status;

	envs = env_variables(env, 0);
	g_data.env = envs;
	g_data.counter = 0;
	g_data.heredoc = 0;
	g_data.status = 0;
	g_data.err = 0;
	last_status = ft_itoa(g_data.status);
	set_value("?", last_status);
	free(last_status);
}

void	main_extra(t_list **splited_str, char *prompt)
{
	char	*last_status;

	add_history(prompt);
	last_status = ft_itoa(g_data.status);
	set_value("?", last_status);
	command_not_found();
	free(last_status);
	free_list(splited_str, prompt);
	g_data.heredoc = 0;
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
		if (g_data.err == 1)
		{
			g_data.err = 0;
			free_list(splited_str, prompt);
			continue ;
		}
		expander(splited_str);
		parser(splited_str);
		executer(0, -1);
		main_extra(splited_str, prompt);
	}
}
