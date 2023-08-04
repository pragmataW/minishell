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
	iter->infile = fd;
	free(iter->full_cmd[i]);
	iter->full_cmd[i] = NULL;
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

int	get_heredoc(int fd, char *input)
{
	char	*line;
	char	*tmp;
	int		id;

	line = NULL;
	id = fork();
	tmp = open_path();
	if (id == 0)
	{
		while (1)
		{
			line = readline("\033[1;31m<< \033[0m ");
			if (!ft_strncmp(line, input))
			{
				free(line);
				return (open(tmp, O_RDONLY, 0644));
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		close(fd);
	}
	else
		wait(NULL);
}
