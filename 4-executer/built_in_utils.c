/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:57:30 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/15 17:22:41 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_exportable(char *var)
{
	int	i;
	int	checkequal;

	checkequal = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			checkequal = 1;
		if (ft_isspace(var[i]))
			return (0);
		if (var[i] == '\"' || var[i] == '\'')
			return (0);
		if (var[i] == '$')
			return (0);
		i++;
	}
	if (checkequal == 0)
		return (0);
	return (1);
}

int	matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**resize_matrix(char	**matrix)
{
	char	**ret;
	int		size;
	int		i;
	int		j;

	size = matrix_size(matrix);
	ret = malloc(sizeof(char *) * size);
	i = 0;
	j = 0;
	while (matrix[i])
	{
		if (ft_strncmp(matrix[i], " " ) == 0)
		{
			i++;
			continue ;
		}
		ret[j] = ft_strdup(matrix[i]);
		i++;
		j++;
	}
	ret[j] = NULL;
	free_matrix(matrix);
	return (ret);
}

void	export_keywords(char *add, int i)
{
	char	**ret;
	int		size;
	char	*tmp;

	size = matrix_size(g_data.env->keys);
	ret = malloc(sizeof(char *) * (size + 2));
	tmp = find_values(g_data.env, add, NULL);
	if (tmp)
	{
		delete_value(add);
		free(tmp);
	}
	while (g_data.env->keys[i])
	{
		ret[i] = ft_strdup(g_data.env->keys[i]);
		i++;
	}
	ret[i] = ft_strdup(add);
	ret[++i] = NULL;
	free_matrix(g_data.env->keys);
	g_data.env->keys = ret;
}
