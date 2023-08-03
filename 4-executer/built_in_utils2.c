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
