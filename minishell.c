/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:58:43 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/15 17:27:02 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

static void	init_global(char **env)
{
	t_env	*envs;
	char	*last_status;

	envs = env_variables(env, 0);
	g_data.env = envs;
	g_data.counter = 0;
	g_data.heredoc = 0;
	g_data.status = 0;
	g_data.err = 0;
	g_data.splitted_str = NULL;
	g_data.pipes = NULL;
	g_data.heredoc_path = NULL;
	last_status = ft_itoa(g_data.status);
	set_value("?", last_status);
	free(last_status);
}

static void	main_extra(t_list **splited_str, char *prompt)
{
	char	*last_status;

	add_history(prompt);
	last_status = ft_itoa(g_data.status);
	set_value("?", last_status);
	command_not_found();
	free(last_status);
	free_list(splited_str, prompt);
	free_parsed(g_data.cmd_table);
	g_data.heredoc = 0;
}

static void	start(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	init_global(env);
	printf(CLEAR_TERM);
	printf(RESET_CURSOR);
	signals_control();
}

static void	prompt_check(char *prompt)
{
	if (!prompt)
	{
		free_global('\0');
		exit(0);
	}
}

int	main(int argc, char *argv[], char **env)
{
	char	*prompt;
	t_list	**splited_str;

	start(argc, argv, env);
	while (1)
	{
		prompt = get_input();
		prompt_check(prompt);
		if (prompt[0] == 0 || is_full_space(prompt) || !quote_check(prompt, 0))
		{
			free(prompt);
			continue ;
		}
		splited_str = lexer(prompt, 0, 0);
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
