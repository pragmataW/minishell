/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:57:56 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/15 17:13:26 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_error(t_table *iter)
{
	terminate_command(iter);
	printf("minishell: parse error no file\n");
	g_data.status = 2;
}

void	command_not_found(void)
{
	if (g_data.status == 127)
		printf("minishell: command cannot execute (not found or syntax err)\n");
	g_data.status = 0;
}

int	quote_check(char *prompt, int i)
{
	int		quote_counter;

	quote_counter = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
		{
			quote_counter++;
			quotes_skipper(&i, prompt);
			if (prompt[i] == '\0')
				break ;
			else
				quote_counter++;
		}
		i++;
	}
	if (quote_counter % 2 == 0)
		return (1);
	else
	{
		printf("minishell: syntax error\n");
		add_history(prompt);
		return (0);
	}
}
