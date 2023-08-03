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
				printf("minishell: parse error no file\n");
				return ;
			}
			if (iter->full_cmd[i + 2])
			{
				printf("minishell: parse error too many arguments\n");
				return ;
			}
			file_name = iter->full_cmd[i + 1];
			fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			iter->outfile = fd;
			iter->full_cmd[i] = NULL;
			iter->full_cmd[i + 1] = NULL;
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
				printf("minishell: parse error no file\n");
				return ;
			}
			if (iter->full_cmd[i + 2])
			{
				printf("minishell: parse error too many arguments\n");
				return ;
			}
			file_name = iter->full_cmd[i + 1];
			fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
			iter->outfile = fd;
			iter->full_cmd[i] = NULL;
			iter->full_cmd[i + 1] = NULL;
			break ;
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
			i++;
		}
		iter = iter->next;
	}
}
