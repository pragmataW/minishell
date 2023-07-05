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

void	expand_dollar(t_list *it, int *i, char *new_str, int *j)
{
	char	*env_key;
	char	*env_var;

	*i = *i + 1;
	data.counter = 0;
	env_key = malloc(sizeof(char ) * 100);
	while (it->command[*i] != ' ' && it->command[*i] != '\''
		&& it->command[*i] != '\"' && it->command[*i] != '\0'
		&& it->command[*i] != '$')
	{
			env_key[data.counter++] = it->command[*i];
			*i = *i + 1;
	}
	env_key[data.counter] = '\0';
	env_var = find_values(data.env, env_key);
	if (env_var != NULL)
	{
		data.counter = 0;
		while (env_var[data.counter])
		{
			new_str[*j] = env_var[data.counter++];
			*j = *j + 1;
		}
	}
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
		while (data.env->tilda[j])
			new_str[(*k)++] = data.env->tilda[j++];
		(*i)++;
	}
	else
		new_str[(*k)++] = iter->command[(*i)++];
}
