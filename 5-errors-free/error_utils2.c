/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:57:59 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/12 20:58:00 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_syntax_check(t_list **lexed_str)
{
	t_list	*i;

	i = *lexed_str;
	if (!i)
		return ;
	if (i->command[0] == '|')
	{
		g_data.err = 1;
		return ;
	}
	while (i)
	{
		if (i->command[0] == '|' && (i->next == NULL
				|| i->next->command[0] == '>'
				|| i->next->command[0] == '<' || i->next->command[0] == '|'))
		{
			g_data.err = 1;
			return ;
		}
		i = i->next;
	}
}

void	redirec_syntax_check(t_list **lexed_str)
{
	t_list	*i;

	i = *lexed_str;
	if (!i)
		return ;
	if (i->command[0] == '>' || i->command[0] == '<')
	{
		g_data.err = 1;
		return ;
	}
	while (i)
	{
		if ((i->command[0] == '<' || i->command[0] == '>') && (i->next == NULL
				|| i->next->command[0] == '>'
				|| i->next->command[0] == '<' || i->next->command[0] == '|'))
		{
			g_data.err = 1;
			return ;
		}
		i = i->next;
	}
}

int	is_full_space(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] != ' ' && prompt[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
