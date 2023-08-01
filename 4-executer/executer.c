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
			{
				execve(iter->cmd_path, iter->full_cmd, NULL);
				exit(0);
			}
			else if (i == 0)
			{
				close(fd[0][0]);
				dup2(fd[0][1], STDOUT_FILENO);
				close(fd[0][1]);
				execve(iter->cmd_path, iter->full_cmd, NULL);
				exit(0);
			}
			else if (i == pc - 1)
			{
				close(fd[pc - 2][1]);
				dup2(fd[pc - 2][0], STDIN_FILENO);
				close(fd[pc - 2][0]);
				execve(iter->cmd_path, iter->full_cmd, NULL);
				exit(0);
			}
			else
			{
				close(fd[j][1]);
				dup2(fd[j][0], STDIN_FILENO);
				close(fd[j][0]);
				close(fd[j + 1][0]);
				dup2(fd[j + 1][1], STDOUT_FILENO);
				close(fd[j + 1][1]);
				execve(iter->cmd_path, iter->full_cmd, NULL);
				exit(0);
			}
		}
		wait(NULL);
		iter = iter->next;
		if (i == 0)
			close(fd[0][1]);
		else if (i == pc - 1)
			close(fd[pc - 2][0]);
		else
		{
			close(fd[j][0]);
			close(fd[j + 1][1]);
		}
	j++;
	i++;
	}
}

