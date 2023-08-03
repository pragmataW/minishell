#include "../minishell.h"

static void	improved_exec(int i, int j, int pc, int **fd)
{
	int		id;
	t_table	*iter;

	iter = *data.cmd_table;
	while (i < pc)
	{
		if (ft_strncmp(iter->cmd_path, "exit") == 0)
			exit(0);
		else if (ft_strncmp(iter->cmd_path, "unset") == 0)
			ft_unset(iter->full_cmd, 1);
		else if (ft_strncmp(iter->cmd_path, "export") == 0)
			ft_export(iter->full_cmd);
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
		wait(NULL);
		iter = iter->next;
		close_main_fd(fd, &j, &i, pc);
	}
}

void	executer(t_table **cmd_table, int i, int j)
{
	int		**fd;

	fd = create_pipes(data.process_count);
	improved_exec(i, j, data.process_count, fd);
}

