#include "../minishell.h"

int	process_counter(t_table **cmd_table)
{
	int		i;
	t_table	*iter;

	i = 0;
	iter = *cmd_table;
	while (iter)
	{
		iter = iter->next;
		i++;
	}
	return (i);
}

int	**create_pipes(int process_count)
{
	int	**fd;
	int	i;

	i = 0;

	fd = malloc(sizeof(int *) * process_count);
	while (i < process_count)
	{
		fd[i] = malloc(sizeof(int) * 2);
		pipe(fd[i]);
		i++;
	}
	return (fd);
}
