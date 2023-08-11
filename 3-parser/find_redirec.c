#include "../minishell.h"

static void	create_redirec(t_table *iter, int i, int fd)
{
	char	*file_name;

	while (iter->full_cmd[i])
	{
		if (!ft_strncmp(iter->full_cmd[i], ">"))
		{
			if (!iter->full_cmd[i + 1])
			{
				parse_error(iter);
				return ;
			}
			file_name = iter->full_cmd[i + 1];
			fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			set_fd(iter, i, fd, 'o');
			break ;
		}
		i++;
	}
}

static void	append_redirec(t_table *iter, int i, int fd)
{
	char	*file_name;

	while (iter->full_cmd[i])
	{
		if (!ft_strncmp(iter->full_cmd[i], ">>"))
		{
			if (!iter->full_cmd[i + 1])
			{
				parse_error(iter);
				return ;
			}
			file_name = iter->full_cmd[i + 1];
			fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			set_fd(iter, i, fd, 'o');
			break ;
		}
		i++;
	}
}

static void	infile_redirec(t_table *iter, int i, int fd)
{
	char	*file_name;

	while (iter->full_cmd[i])
	{
		if (!ft_strncmp(iter->full_cmd[i], "<"))
		{
			if (!iter->full_cmd[i + 1])
			{
				parse_error(iter);
				return ;
			}
			file_name = iter->full_cmd[i + 1];
			fd = open(file_name, O_RDONLY, 0644);
			set_fd(iter, i, fd, 'i');
			break ;
		}
		i++;
	}
}

static void	heredoc_redirec(t_table *iter, int i, int fd)
{
	char	*path;

	while (iter->full_cmd[i])
	{
		if (!ft_strncmp(iter->full_cmd[i], "<<"))
		{
			if (!iter->full_cmd[i + 1])
			{
				parse_error(iter);
				return ;
			}
			path = open_path();
			fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			get_heredoc(fd, iter->full_cmd[i + 1], 0);
			fd = open(path, O_RDONLY, 0644);
			set_heredoc_fd(iter, i, fd);
			free(path);
		}
		i++;
	}
}

void	find_redirec(t_table **root)
{
	t_table	*iter;
	int		i;
	int		cmd_size;

	iter = *root;
	while (iter)
	{
		i = 0;
		while (iter->full_cmd[i])
		{
			cmd_size = ft_strlen(iter->full_cmd[i]);
			if (!ft_strncmp(iter->full_cmd[i], ">") && cmd_size == 1)
				create_redirec(iter, 0, 0);
			if (!ft_strncmp(iter->full_cmd[i], ">>") && cmd_size == 2)
				append_redirec(iter, 0, 0);
			if (!ft_strncmp(iter->full_cmd[i], "<") && cmd_size == 1)
				infile_redirec(iter, 0, 0);
			if (!ft_strncmp(iter->full_cmd[i], "<<") && cmd_size == 2)
				heredoc_redirec(iter, 0, 0);
			i++;
		}
		iter = iter->next;
	}
}
