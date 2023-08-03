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
