#include "../minishell.h"

t_env	*env_variables(char **env, int env_count)
{
	t_env	*ret;
	int		i;
	int		s_i;

	while (env[env_count])
		env_count++;

	ret = malloc(sizeof(t_env));
	ret->keys = malloc(sizeof(char *) * (env_count + 1));
	ret->values = malloc(sizeof(char *) * (env_count + 1));
	ret->keys[env_count] = NULL;
	ret->values[env_count] = NULL;
	i = 0;
	while (env[i])
	{
		s_i = find_char(env[i], '=');
		ret->keys[i] = malloc(sizeof(char) * (s_i + 1));
		ret->values[i] = malloc(sizeof(char) * (ft_strlen(env[i]) - s_i + 1));
		allocator(ret->keys[i], env[i], s_i);
		allocator(ret->values[i], &(env[i][s_i + 1]), ft_strlen(env[i]) - s_i);
		i++;
	}
	ret->tilda = find_values(ret, "HOME");
	return (ret);
}
