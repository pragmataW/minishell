#include "../minishell.h"

static int	main_builtin(t_table *iter)
{
	int	status;

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
		printf(CLEAR_TERM);
		printf(RESET_CURSOR);
		status = 0;
	}
	return (status);
}

static void	improved_exec(int i, int j, int pc, int **fd)
{
	int		id;
	t_table	*iter;

	iter = *data.cmd_table;
	while (i < pc && data.heredoc == 0)
	{
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
		data.status = main_builtin(iter);
		wait(&data.status);
		if (WIFEXITED(data.status))
			data.status = WEXITSTATUS(data.status);
		iter = iter->next;
		close_main_fd(fd, &j, &i, pc);
	}
}

void	executer(int i, int j)
{
	int		**fd;
	char	*path;

	path = open_path();
	fd = create_pipes(data.process_count);
	improved_exec(i, j, data.process_count, fd);
	unlink(path);
}

