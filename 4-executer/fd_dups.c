#include "../minishell.h"

void	single_exec(t_table *iter)
{
	if (is_builtin(iter->cmd_path))
		builtin_execv(iter);
	else
		execve(iter->cmd_path, iter->full_cmd, NULL);
	exit(0);
}

void	dup_first(t_table *iter, int **fd)
{
	close(fd[0][0]);
	dup2(fd[0][1], STDOUT_FILENO);
	close(fd[0][1]);
	if (is_builtin(iter->cmd_path))
		builtin_execv(iter);
	else
		execve(iter->cmd_path, iter->full_cmd, NULL);
	exit(0);
}

void	dup_last(t_table *iter, int **fd, int pc)
{
	close(fd[pc - 2][1]);
	dup2(fd[pc - 2][0], STDIN_FILENO);
	close(fd[pc - 2][0]);
	if (is_builtin(iter->cmd_path))
		builtin_execv(iter);
	else
		execve(iter->cmd_path, iter->full_cmd, NULL);
	exit(0);
}

void	dup_mids(t_table *iter, int **fd, int j)
{
	close(fd[j][1]);
	dup2(fd[j][0], STDIN_FILENO);
	close(fd[j][0]);
	close(fd[j + 1][0]);
	dup2(fd[j + 1][1], STDOUT_FILENO);
	close(fd[j + 1][1]);
	if (is_builtin(iter->cmd_path))
		builtin_execv(iter);
	else
		execve(iter->cmd_path, iter->full_cmd, NULL);
	exit(0);
}

void	close_main_fd(int **fd, int j, int i, int pc)
{
	if (i == 0)
		close(fd[0][1]);
	else if (i == pc - 1)
		close(fd[pc - 2][0]);
	else
	{
		close(fd[j][0]);
		close(fd[j + 1][1]);
	}
}
