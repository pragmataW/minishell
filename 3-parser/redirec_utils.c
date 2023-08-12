#include "../minishell.h"

void	terminate_command(t_table *iter)
{
	int	i;

	i = 1;
	free(iter->cmd_path);
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
	if (fd == -1)
	{
		printf("minishell: no such file or directory\n");
		terminate_command(iter);
		return ;
	}
	if (opt == 'i')
		iter->infile = fd;
	else if (opt == 'o')
		iter->outfile = fd;
	free(iter->full_cmd[i]);
	iter->full_cmd[i] = NULL;
	free(iter->full_cmd[i + 1]);
	iter->full_cmd[i + 1] = NULL;
}

void	set_heredoc_fd(t_table *iter, int i, int fd)
{
	if (g_data.heredoc == 0)
		fd = open("err", O_CREAT, 777);
	iter->infile = fd;
	free(iter->full_cmd[i]);
	free(iter->full_cmd[i + 1]);
	iter->full_cmd[i] = NULL;
	iter->full_cmd[i + 1] = NULL;
	g_data.heredoc = 1;
}

char	*open_path(void)
{
	char	*path;
	char	*ret;

	path = getcwd(NULL, 0);
	ret = ft_strjoin(path, "/minishell_tmp");
	free(path);
	return (ret);
}

void	get_heredoc(int fd, char *input, int id)
{
	char	*line;

	line = NULL;
	g_data.heredoc = 1;
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, heredoc_sig);
		while (1)
		{
			line = readline("\033[1;31m<< \033[0m ");
			if (!ft_strncmp(line, input))
			{
				free(line);
				exit(1);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	else
		wait(&g_data.heredoc);
}
