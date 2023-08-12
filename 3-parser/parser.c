/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:57:19 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/12 20:57:20 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
