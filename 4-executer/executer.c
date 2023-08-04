#include "../minishell.h"

static void	main_builtin(t_table *iter)
{
	if (ft_strncmp(iter->cmd_path, "exit") == 0)
		exit(0);
	else if (ft_strncmp(iter->cmd_path, "unset") == 0)
		ft_unset(iter->full_cmd, 1);
	else if (ft_strncmp(iter->cmd_path, "export") == 0)
		ft_export(iter->full_cmd);
	else if (ft_strncmp(iter->cmd_path, "cd") == 0)
		ft_cd(iter->full_cmd);
	else if (ft_strncmp(iter->cmd_path, "clr") == 0)
	{
		printf(CLEAR_TERM);
		printf(RESET_CURSOR);
	}
}

static void	improved_exec(int i, int j, int pc, int **fd)
{
	int		id;
	t_table	*iter;

	iter = *data.cmd_table;
	while (i < pc)
	{
		main_builtin(iter);
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
	char	**argv;
	char	*path;
	int		id;

	path = open_path();
	argv = malloc(sizeof(char *) * 4);
	argv[0] = ft_strdup("rm");
	argv[1] = ft_strdup("-rf");
	argv[2] = ft_strdup(path);
	argv[3] = NULL;
	fd = create_pipes(data.process_count);
	improved_exec(i, j, data.process_count, fd);
	id = fork();
	if (id == 0)
		execve("/usr/bin/rm", argv, NULL);
	else
		wait(NULL);
}

