#include "minishell.h"

static char	*get_uname(void)
{
	char	*uname;

	uname = find_values(data.env, "USER", NULL);
	return (uname);
}

static char	*get_pwd(void)
{
	char	*pwd;

	pwd = find_values(data.env, "PWD", NULL);
	return (pwd);
}

static char	*get_fullstr(void)
{
	char	*uname;
	char	*pwd;
	char	*ret;
	char	*tmp;

	uname = get_uname();
	pwd = get_pwd();
	ret = ft_strjoin(RED, uname);
	tmp = ft_strdup(ret);
	free(ret);
	ret = ft_strjoin(tmp, T);
	free(tmp);
	tmp = ft_strjoin(ret, pwd);
	free(ret);
	ret = ft_strjoin(tmp, LAST_TXT);
	free(tmp);
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
