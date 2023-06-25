#include "../minishell.h"

char	*find_values(t_env *env, char *kw)
{
	int	i;

	i = 0;
	while (env->keys[i] != NULL)
	{
		if (ft_strncmp(env->keys[i], kw, ft_strlen(env->keys[i])) == 0)
			return (ft_strdup(env->values[i]));
		i++;
	}
	return (NULL);
}

