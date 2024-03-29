/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:56:39 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/12 21:02:02 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	lexer_extra(char *prompt, int *i, char **tmp)
{
	while ((prompt[*i] == ' ' || prompt[*i] == '\t') && prompt[*i] != '\0')
		*i = *i + 1;
	*tmp = &prompt[*i];
	while (prompt[*i] != ' ' && prompt[*i] != '\t' && prompt[*i] != '\0')
	{
		if (prompt[*i] == 34 || prompt[*i] == 39)
			quotes_skipper(i, prompt);
		*i = *i + 1;
	}
}

t_list	**lexer(char *prompt, int i, int end)
{
	t_list	*cmd;
	t_list	**root;
	t_list	**ret;
	char	*command;
	char	*tmp;

	root = malloc(sizeof(t_list *));
	*root = NULL;
	end = ft_strlen(prompt) - 1;
	while (prompt[end] == ' ' || prompt[end] == '\t' || prompt[end] == '\0')
		end--;
	while (prompt[i] && i <= end)
	{
		lexer_extra(prompt, &i, &tmp);
		command = malloc(sizeof(char) * ((&(prompt[i]) - tmp) + 1));
		allocator(command, tmp, &(prompt[i]) - tmp);
		cmd = ft_lstnew(command);
		free(command);
		ft_lstadd_back(root, cmd);
	}
	ret = trim_all(root);
	free_list(root, NULL);
	errors(ret, prompt);
	return (ret);
}
