#include "../minishell.h"

t_table	**parser(t_list **expanded_str)
{
	t_table	**root;

	root = fill_node(expanded_str, 0);
	expand_cmd(root, data.env, 0);
	data.process_count = process_counter(root);
	data.cmd_table = root;
	return (root);
}
