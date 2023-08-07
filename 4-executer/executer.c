#include "../minishell.h"

static int	main_builtin(t_table *iter)
{
	int	status;

	status = -1;
	if (ft_strncmp(iter->cmd_path, "exit") == 0)
		exit(0);
	else if (ft_strncmp(iter->cmd_path, "unset") == 0)
		status = ft_unset(iter->full_cmd, 1);
	else if (ft_strncmp(iter->cmd_path, "export") == 0)
		status = ft_export(iter->full_cmd);
	else if (ft_strncmp(iter->cmd_path, "cd") == 0)
		status = ft_cd(iter->full_cmd);
	else if (ft_strncmp(iter->cmd_path, "clr") == 0)
	{
		status = 0;
		printf(CLEAR_TERM);
		printf(RESET_CURSOR);
	}
	return (status);
}

static void	exit_status(void)
{
	wait(&g_data.status);
	if (WIFEXITED(g_data.status))
		g_data.status = WEXITSTATUS(g_data.status);
}

static void	improved_exec(int i, int j, int pc, int **fd)
{
	int		id;
	t_table	*iter;

	iter = *g_data.cmd_table;
	while (i < pc && g_data.heredoc == 0)
	{
		g_data.status = main_builtin(iter);
		if (g_data.status != -1)
			return ;
		id = fork();
		if (id == 0)
		{
			if (pc == 1)
				single_exec(iter);
			else if (i == 0)
				dup_first(iter, fd);
			else if (i == pc - 1)
				dup_last(iter, fd, pc);
			else
				dup_mids(iter, fd, j);
		}
		exit_status();
		iter = iter->next;
		close_main_fd(fd, &j, &i, pc);
	}
}

void	executer(int i, int j)
{
	int		**fd;
	char	*path;

	path = open_path();
	fd = create_pipes(g_data.process_count);
	improved_exec(i, j, g_data.process_count, fd);
	unlink(path);
	unlink("err");
}
