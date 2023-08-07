#include "../minishell.h"

static void	expand_cmd_extra(int i, char **paths, t_table *iter)
{
	char	*new_path;

	while (paths[i++])
	{
		new_path = find_path(paths[i], iter->cmd_path);
		if (access(new_path, F_OK) == 0)
			iter->cmd_path = ft_strdup(new_path);
		free(new_path);
	}
	if (iter->cmd_path[0] == '.' && iter->cmd_path[1] == '/')
		expand_binary(iter);
}

void	expand_cmd(t_table **table, int i)
{
	t_table	*iter;
	char	**paths;
	char	*value;

	iter = *table;
	value = find_values(g_data.env, "PATH", NULL);
	paths = ft_split(value, ':');
	while (iter && paths)
	{
		i = 0;
		if (!is_builtin(iter->cmd_path))
			expand_cmd_extra(i, paths, iter);
		iter = iter->next;
	}
	free_matrix(paths);
	free(value);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "pwd"))
		return (1);
	if (!ft_strncmp(cmd, "env"))
		return (1);
	if (!ft_strncmp(cmd, "cd"))
		return (1);
	if (!ft_strncmp(cmd, "export"))
		return (1);
	if (!ft_strncmp(cmd, "unset"))
		return (1);
	if (!ft_strncmp(cmd, "echo"))
		return (1);
	if (!ft_strncmp(cmd, "exit"))
		return (1);
	return (0);
}

void	expand_binary(t_table *node)
{
	char	*new_command;
	int		i;
	int		j;
	int		len;

	i = 2;
	j = 0;
	len = ft_strlen(&node->cmd_path[2]);
	new_command = malloc(sizeof(char) * (len + 1));
	while (node->cmd_path[i] != '\0')
	{
		new_command[j] = node->cmd_path[i];
		i++;
		j++;
	}
	new_command[j] = '\0';
	node->cmd_path = new_command;
}
