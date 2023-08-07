#include "../minishell.h"

void	expand_quote(t_list *iter, int *i, char *new_str, int *j)
{
	*i = *i + 1;
	while (iter->command[*i] != '\"' && iter->command[*i])
	{
		if (iter->command[*i] == '$')
			expand_dollar(iter, i, new_str, j);
		else
		{
			new_str[*j] = iter->command[*i];
			*j = *j + 1;
			*i = *i + 1;
		}
	}
	*i = *i + 1;
}

void	expand_single_quote(t_list *iter, int *i, char *new_str, int *j)
{
	*i = *i + 1;
	while (iter->command[*i] != '\'' && iter->command[*i])
	{
		new_str[*j] = iter->command[*i];
		*j = *j + 1;
		*i = *i + 1;
	}
	*i = *i + 1;
}

static void	expand_dollar_extra(char *new_str, char *env_var, int *j)
{
	g_data.counter = 0;
	while (env_var[g_data.counter])
	{
		new_str[*j] = env_var[g_data.counter++];
		*j = *j + 1;
	}
}

void	expand_dollar(t_list *it, int *i, char *new_str, int *j)
{
	char	*env_key;
	char	*env_var;

	*i = *i + 1;
	g_data.counter = 0;
	env_key = malloc(sizeof(char ) * 100);
	while (it->command[*i] != ' ' && it->command[*i] != '\''
		&& it->command[*i] != '\"' && it->command[*i] != '\0'
		&& it->command[*i] != '$')
	{
			env_key[g_data.counter++] = it->command[*i];
			*i = *i + 1;
	}
	env_key[g_data.counter] = '\0';
	env_var = find_values(g_data.env, env_key, NULL);
	if (env_var != NULL)
		expand_dollar_extra(new_str, env_var, j);
	free(env_key);
	free(env_var);
}

void	tilda_extra(t_list *iter, int *i, char *new_str, int *k)
{
	int		j;
	char	c;

	j = 0;
	if (iter->command[*i] == '\'' || iter->command[*i] == '\"')
	{
		c = iter->command[*i];
		new_str[(*k)++] = iter->command[(*i)++];
		while (iter->command[*i] != '\0' && iter->command[*i] != c)
			new_str[(*k)++] = iter->command[(*i)++];
	}
	if (iter->command[*i] == '~' && iter->command[*i - 1] != '/')
	{
		while (g_data.env->tilda[j])
			new_str[(*k)++] = g_data.env->tilda[j++];
		(*i)++;
	}
	else
		new_str[(*k)++] = iter->command[(*i)++];
}
