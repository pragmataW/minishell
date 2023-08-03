#include "../minishell.h"

void	export_value(char *add)
{
	char	**ret;
	int		size;
	int		i;

	size = matrix_size(data.env->values);
	ret = malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (data.env->values[i])
	{
		ret[i] = ft_strdup(data.env->values[i]);
		i++;
	}
	ret[i] = ft_strdup(add);
	ret[++i] = NULL;
	free_matrix(data.env->values);
	data.env->values = ret;
}

void	delete_value(char *delete)
{
	int		i;
	int		index;
	char	*tmp;

	tmp = find_values(data.env, delete, &index);
	if (tmp)
		free(tmp);
	else
		return ;
	free(data.env->keys[index]);
	free(data.env->values[index]);
	data.env->keys[index] = ft_strdup(" ");
	data.env->values[index] = ft_strdup(" ");
	data.env->keys = resize_matrix(data.env->keys);
	data.env->values = resize_matrix(data.env->values);
}

void	set_value(char *add, char *value)
{
	export_keywords(add, 0);
	export_value(value);
}
