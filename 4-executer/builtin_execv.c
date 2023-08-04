#include "../minishell.h"

void	builtin_execv(t_table *node)
{
	if (ft_strncmp(node->cmd_path, "echo") == 0)
		ft_echo(node->full_cmd);
	else if (ft_strncmp(node->cmd_path, "pwd") == 0)
		ft_pwd();
	else if (ft_strncmp(node->cmd_path, "env") == 0)
		ft_env();
	exit(0);
}
