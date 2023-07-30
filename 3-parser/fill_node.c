#include "../minishell.h"

int	node_counter(t_list *list)
{
	int		ret;
	t_list	*iter;

	ret = 0;
	iter = list;
	while (iter && ft_strncmp(iter->command, "|") != 0)
	{
		ret++;
		iter = iter->next;
	}
	return (ret);
}

t_table	**fill_node(t_list **list, int i)
{
	t_table	**root;
	t_table	*node;
	t_list	*iter;

	root = malloc(sizeof(t_table *));
	*root = NULL;
	iter = *list;
	while (iter)
	{
		i = 0;
		node = malloc(sizeof(t_table));
		node->cmd_path = iter->command;
		node->full_cmd = malloc(sizeof(char *) * (node_counter(iter) + 1));
		while (iter && ft_strncmp(iter->command, "|") != 0)
		{
			node->full_cmd[i] = ft_strdup(iter->command);
			iter = iter->next;
			i++;
		}
		node->full_cmd[i] = NULL;
		node->infile = 0;
		node->outfile = 1;
		table_add_back(root, node);
		if (iter)
			iter = iter->next;
	}
	return (root);
}
