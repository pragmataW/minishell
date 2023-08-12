/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:58:41 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/12 20:59:43 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_uname(void)
{
	char	*uname;

	uname = find_values(g_data.env, "USER", NULL);
	return (uname);
}

static char	*get_pwd(void)
{
	char	*pwd;

	pwd = find_values(g_data.env, "PWD", NULL);
	return (pwd);
}

static char	*get_fullstr(void)
{
	char	*uname;
	char	*pwd;
	char	*ret;
	char	*tmp;
	char	*txt;

	txt = ft_strjoin(T, PWD_COLOR);
	uname = get_uname();
	pwd = get_pwd();
	ret = ft_strjoin(RED, uname);
	free(uname);
	tmp = ft_strdup(ret);
	free(ret);
	ret = ft_strjoin(tmp, txt);
	free(tmp);
	tmp = ft_strjoin(ret, pwd);
	free(pwd);
	free(ret);
	ret = ft_strjoin(tmp, LAST_TXT);
	free(tmp);
	free(txt);
	return (ret);
}

char	*get_input(void)
{
	char	*input;
	char	*fullstr;

	fullstr = get_fullstr();
	input = readline(fullstr);
	free(fullstr);
	return (input);
}
