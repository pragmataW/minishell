#include "../minishell.h"

char	*find_values(t_env *env, char *kw)
{
	int	i;

	i = 0;
	while (env->keys[i] != NULL)
	{
		if (ft_strncmp(env->keys[i], kw) == 0)
			return (ft_strdup(env->values[i]));
		i++;
	}
	return (NULL);
}

char	*ft_str_realloc(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * strlen(str) + 1);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	free(str);
	return (ret);
}

void	new_command(t_list *iter, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	free(iter->command);
	iter->command = malloc((sizeof(char) * len) + 1);
	while (str[i])
	{
		iter->command[i] = str[i];
		i++;
	}
	iter->command[i] = '\0';
}
