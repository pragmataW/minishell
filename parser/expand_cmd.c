#include "../minishell.h"

void expand_cmd(t_list **splited_str, t_env *env, int i)
{
    t_list *iter;
    char **paths;

    iter = *splited_str;
    while (iter)
    {
        if (!is_builtin(iter->command))
        {
            paths = ft_split(find_values(env, "PATH"), ':');
            while (paths[i])
            {
            paths[i] = ft_strjoin(paths[i], "/");
            paths[i] = ft_strjoin(paths[i], iter->command);
            if (access(paths[i], F_OK) == 0)
                new_command(iter, paths[i]);
            i++;
            } 
            i = 0;      
        }
        iter = iter->next;
    }
}

int	is_builtin(char *cmd)
{
	int		l;

	if (!cmd)
		return (0);
	l = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd") && l == 3)
		return (1);
	if (!ft_strncmp(cmd, "env") && l == 3)
		return (1);
	if (!ft_strncmp(cmd, "cd") && l == 2)
		return (1);
	if (!ft_strncmp(cmd, "export") && l == 6)
		return (1);
	if (!ft_strncmp(cmd, "unset") && l == 5)
		return (1);
	if (!ft_strncmp(cmd, "echo") && l == 4)
		return (1);
	if (!ft_strncmp(cmd, "exit") && l == 4)
		return (1);
	return (0);
}