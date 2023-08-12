/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:57:17 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/12 21:00:02 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	table_add_back(t_table **lst, t_table *new)
{
	if (!*lst)
		*lst = new;
	else
		table_last(*lst)->next = new;
}

t_table	*table_new(char *content)
{
	t_table	*ptr;

	ptr = (t_table *)malloc(sizeof(t_table));
	if (!ptr)
		return (NULL);
	ptr->cmd_path = ft_strdup(content);
	return (ptr);
}

t_table	*table_last(t_table *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

char	*find_path(char *path, char *command)
{
	char	*ret;
	char	*slash;

	slash = ft_strjoin(path, "/");
	ret = ft_strjoin(slash, command);
	free(slash);
	return (ret);
}
