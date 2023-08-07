#include "../minishell.h"

void	parser(t_list **expanded_str)
{
	t_table	**root;

	root = fill_node(expanded_str, 0);
	expand_cmd(root, 0);
	find_redirec(root);
	g_data.process_count = process_counter(root);
	g_data.cmd_table = root;
}
