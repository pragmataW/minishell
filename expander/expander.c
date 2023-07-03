#include "../minishell.h"

// static void	expand_tilda(t_list *n, char **env)
// {
// 	t_env	*envs;
// 	char	*new_str;
// 	char	*home;

// 	envs = env_variables(env, 0);
// 	home = find_values(envs, "HOME");
// 	if (n->command[1] == '/')
// 	{
// 		new_str = ft_strjoin(home, &n->command[1]);
// 		free(n->command);
// 		n->command = new_str;
// 	}
// 	else if (n->command[1] == '\0')
// 	{
// 		new_str = home;
// 		free(n->command);
// 		n->command = new_str;
// 	}
// 	else
// 		exit(printf("sh:no such user or named directry: %s", &n->command[1]));
// }

void	expand_dollar(t_list **splitted_str, t_env *env, int i, int j)
{
	t_list	*iter;
	char	*new_str;
	char	*env_var;
	char	*env_key;
	int		k;

	iter = *splitted_str;
	while (iter)
	{
		i = 0;
		new_str = malloc(sizeof(char) * 10000);
		env_var = malloc(sizeof(char) * 1);
		env_key = malloc(sizeof(char) * 100);
		k = 0;
		while (iter->command[i])
		{
			if (iter->command[i] == '\'')
			{
				i++;
				while (iter->command[i] != '\'' && iter->command[i] != '\0')
					new_str[k++] = iter->command[i++];
			}
			if (iter->command[i] == '\"')
				i++;
			if (iter->command[i] == '$')
			{
				i++;
				while (iter->command[i] != ' ' && iter->command[i] != '\''
					|| iter->command[i] != '\"' && iter->command[i] != '\0'
					|| iter->command[i] != '$')
					env_key[j++] = iter->command[i++];
				env_key[j] = '\0';
				env_key = ft_str_realloc(env_key);
				free(env_var);
				env_var = find_values(env, env_key);
				free(env_key);
				j = 0;
				while (env_var[j])
					new_str[k++] = env_var[j++];
			}
			new_str[k++] = iter->command[i++];
		}
		new_str[k] = '\0';
		new_str = ft_str_realloc(new_str);
		printf("%s\n", new_str);
		new_command(iter, new_str);
		free(new_str);
		iter = iter->next;
	}
}

void	expander(t_list **splitted_str, char **env)
{
	t_env	*envs;
	t_list	*iter;

	envs = env_variables(env, 0);
	iter = *splitted_str;
	expand_dollar(splitted_str, envs, 0, 0);
}
