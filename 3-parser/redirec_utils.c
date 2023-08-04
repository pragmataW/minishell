#include "../minishell.h"

void	terminate_command(t_table *iter)
{
	int	i;

	i = 1;
	iter->cmd_path = NULL;
	while (iter->full_cmd[i])
	{
		free(iter->full_cmd[i]);
		iter->full_cmd[i] = NULL;
		i++;
	}
}

void	set_fd(t_table *iter, int i, int fd, char opt)
{
	if (opt == 'i')
		iter->infile = fd;
	else if (opt == 'o')
		iter->outfile = fd;
	free(iter->full_cmd[i]);
	iter->full_cmd[i] = NULL;
	free(iter->full_cmd[i + 1]);
	iter->full_cmd[i + 1] = NULL;
}
