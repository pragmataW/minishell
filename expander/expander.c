#include "../minishell.h"

static void	expand_tilda(t_list **splitted_str, char **env, int i, int j)
{
	char	*new_str;
	char	*var;
	t_env	*envs;
	t_list	*iter;
	int		k;

	envs = env_variables(env, 0);
	iter = *splitted_str;
	var = envs->tilda;
	while (iter)
	{
		k = 0;
		i = 0;
		new_str = malloc(sizeof(char) * 10000);
		while (iter->command[i])
		{
			j = 0;
			if (iter->command[i] == '\'')
			{
				new_str[k++] = iter->command[i++];
				while (iter->command[i] != '\0' && iter->command[i] != '\'')
					new_str[k++] = iter->command[i++];
			}
			if (iter->command[i] == '\"')
			{
				new_str[k++] = iter->command[i++];
				while (iter->command[i] != '\0' && iter->command[i] != '\"')
					new_str[k++] = iter->command[i++];
			}
			if (iter->command[i] == '~')
			{
				while (var[j])
					new_str[k++] = var[j++];
				i++;
			}
			else
				new_str[k++] = iter->command[i++];
		}
		new_str[k] = '\0';
		new_str = ft_str_realloc(new_str);
		new_command(iter, new_str);
		free(new_str);
		iter = iter->next;
	}
}

void	expand_var(t_list **splitted_str, int i, int j)
{
	t_list	*iter;
	char	*new_str;

	iter = *splitted_str;
	while (iter)
	{
		i = 0;
		j = 0;
		new_str = malloc(sizeof(char) * 10000);
		while (iter->command[i])
		{
			if (iter->command[i] == '\"')
				expand_quote(iter, &i, new_str, &j);
			else if (iter->command[i] == '\'')
				expand_single_quote(iter, &i, new_str, &j);
			else
				expand_normal(iter, &i, new_str, &j);
		}
		new_str[j] = '\0';
		new_command(iter, new_str);
		iter = iter->next;
	}
}

void	expander(t_list **splitted_str, char **env)
{
	t_env	*envs;

	envs = env_variables(env, 0);
	expand_tilda(splitted_str, env, 0, 0);
	expand_var(splitted_str, 0, 0);
}
