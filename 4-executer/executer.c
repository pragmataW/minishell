#include "../minishell.h"

void	executer(t_table **cmd_table, int i, int j)
{
	t_table	*iter;
	int		pc;
	int		**fd;
	int		id;

	iter = *cmd_table;
	pc = process_counter(cmd_table);
	fd = create_pipes(pc);
	j = -1;
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

