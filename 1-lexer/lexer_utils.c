/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:56:36 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/15 17:15:14 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocator(char *ret, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
}

void	quotes_skipper(int *i, char *prompt)
{
	char	quotes;

	quotes = prompt[*i];
	*i = *i + 1;
	while (prompt[*i] != '\0' && prompt[*i] != quotes)
		*i = *i + 1;
}

int	command_len(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>' && cmd[i] != '\0')
		i++;
	if (i == 0)
	{
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (i);
}
