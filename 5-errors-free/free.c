#include "../minishell.h"

void	free_list(t_list **list, char *prompt)
{
	t_list	*iter;
	t_list	*tmp;

	iter = *list;
	if (prompt)
		free(prompt);
	while (iter)
	{
		tmp = iter->next;
		free(iter->command);
		free(iter);
		iter = tmp;
	}
	free(list);
}

void	free_parsed(t_table **parsed)
{
	t_table	*iter;
	t_table	*tmp;

	iter = *parsed;
	while (iter)
	{
		tmp = iter->next;
		free(iter->cmd_path);
		free(iter->full_cmd);
		free(iter);
		iter = tmp;
	}
	free(parsed);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_fd(int **fd)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
