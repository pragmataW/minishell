#include "../minishell.h"

void	improved_exec(int i, int j, int pc, int **fd)
{
	int		id;
	t_table	*iter;

	iter = *data.cmd_table;
	while (i < pc)
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
		wait(NULL);
		iter = iter->next;
		close_main_fd(fd, j, i, pc);
	j++;
	i++;
	}
}

void	executer(t_table **cmd_table, int i, int j)
{
	int		**fd;

	fd = create_pipes(data.process_count);
	improved_exec(i, j, data.process_count, fd);
}

