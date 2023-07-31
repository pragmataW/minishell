#include "../minishell.h"

void	expand_cmd(t_table **table, t_env *env, int i)
{
	t_table	*iter;
	char	**paths;
	char	*new_path;

	iter = *table;
	paths = ft_split(find_values(env, "PATH"), ':');
	while (iter)
	{
		i = 0;
		if (!is_builtin(iter->cmd_path))
		{
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
		iter = iter->next;
	}
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
