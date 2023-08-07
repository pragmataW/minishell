#include "../minishell.h"

void	export_value(char *add)
{
	char	**ret;
	int		size;
	int		i;

	size = matrix_size(g_data.env->values);
	ret = malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (g_data.env->values[i])
	{
		ret[i] = ft_strdup(g_data.env->values[i]);
		i++;
	}
	ret[i] = ft_strdup(add);
	ret[++i] = NULL;
	free_matrix(g_data.env->values);
	g_data.env->values = ret;
}

void	delete_value(char *delete)
{
	int		index;
	char	*tmp;

	tmp = find_values(g_data.env, delete, &index);
	if (tmp)
		free(tmp);
	else
		return ;
	free(g_data.env->keys[index]);
	free(g_data.env->values[index]);
	g_data.env->keys[index] = ft_strdup(" ");
	g_data.env->values[index] = ft_strdup(" ");
	g_data.env->keys = resize_matrix(g_data.env->keys);
	g_data.env->values = resize_matrix(g_data.env->values);
}

void	set_value(char *add, char *value)
{
	export_keywords(add, 0);
	export_value(value);
}
