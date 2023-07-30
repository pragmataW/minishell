#include "../minishell.h"

void	table_add_back(t_table **lst, t_table *new)
{
	if (!*lst)
		*lst = new;
	else
		table_last(*lst)->next = new;
}

t_table	*table_last(t_table *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_table	*table_new(void)
{
	t_table	*ptr;

	ptr = (t_table *)malloc(sizeof(t_table));
	if (!ptr)
		return (NULL);
	ptr->cmd_path = NULL;
	ptr->full_cmd = NULL;
	ptr->infile = 0;
	ptr->outfile = 0;
	ptr->next = NULL;
	return (ptr);
}
