/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:58:03 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/12 20:58:04 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_list **list, char *prompt)
{
	t_list	*iter;
	t_list	*tmp;

	iter = *list;
	if (prompt)
		free(prompt);
	while (iter)
	{
		tmp = iter->next;
		free(iter->command);
		free(iter);
		iter = tmp;
	}
	free(list);
}

void	free_parsed(t_table **parsed)
{
	t_table	*iter;
	t_table	*tmp;

	iter = *parsed;
	while (iter)
	{
		tmp = iter->next;
		free(iter->cmd_path);
		free_matrix(iter->full_cmd);
		free(iter);
		iter = tmp;
	}
	free(parsed);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_fd(int **fd)
{
	int	i;

	i = 0;
	while (i < g_data.process_count)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	free_global(char opt)
{
	free_matrix(g_data.env->keys);
	free_matrix(g_data.env->values);
	free(g_data.env->tilda);
	free(g_data.env);
	if (opt == 'e')
	{
		if (g_data.cmd_table)
			free_parsed(g_data.cmd_table);
		if (g_data.heredoc_path)
			free(g_data.heredoc_path);
		if (g_data.splitted_str)
			free_list(g_data.splitted_str, NULL);
		if (g_data.pipes)
			free_fd(g_data.pipes);
	}
}
