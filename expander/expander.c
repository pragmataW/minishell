#include "../minishell.h"

static void	expand_quote(t_list *n, char **env)
{
	return ; //! Yapilacak
}

static void	expand_dollar(t_list *node, char **env)
{
	t_env	*envs;
	char	*new_str;

	envs = env_variables(env, 0);
	new_str = find_values(envs, &node->command[1]);
	free(node->command);
	node->command = new_str;
}

static void	expand_tilda(t_list *n, char **env)
{
	t_env	*envs;
	char	*new_str;
	char	*home;

	envs = env_variables(env, 0);
	home = find_values(envs, "HOME");
	if (n->command[1] == '/')
	{
		new_str = ft_strjoin(home, &n->command[1]);
		free(n->command);
		n->command = new_str;
	}
	else if (n->command[1] == '\0')
	{
		new_str = home;
		free(n->command);
		n->command = new_str;
	}
	else
		exit(printf("sh:no such user or named directry: %s", &n->command[1]));
}

void	expander(t_list **splitted_str, char **env)
{
	t_env	*envs;
	t_list	*iter;

	envs = env_variables(env, 0);
	iter = *splitted_str;
	while (iter)
	{
		if (iter->command[0] == '\"' && ft_strrchr(iter->command, '$') != 0)
			expand_quote(); //! YAPILACAK
		else if (iter->command[0] == '$')
			expand_dollar(iter, env);
		else if (iter->command[0] == '~')
			expand_tilda(iter, env);
		iter = iter->next;
	}
}
