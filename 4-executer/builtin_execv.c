#include "../minishell.h"

void	builtin_execv(t_table *node)
{
	if (ft_strncmp(node->cmd_path, "echo") == 0)
		ft_echo(node->full_cmd);
	else if (ft_strncmp(node->cmd_path, "pwd") == 0)
		ft_pwd();
	else if (ft_strncmp(node->cmd_path, "env") == 0)
		ft_env();
	else if (ft_strncmp(node->cmd_path, "unset") == 0)
		ft_unset(node->full_cmd, 1);
}
