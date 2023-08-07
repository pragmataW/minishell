#include "../minishell.h"

static void	go_home(void)
{
	char	*path;

	path = find_values(g_data.env, "HOME", NULL);
	set_value("OLDPWD", getcwd(NULL, 0));
	chdir(path);
	set_value("PWD", getcwd(NULL, 0));
}

static void	go_oldpwd(void)
{
	char	*path;

	path = find_values(g_data.env, "OLDPWD", NULL);
	set_value("OLDPWD", getcwd(NULL, 0));
	chdir(path);
	set_value("PWD", getcwd(NULL, 0));
}

static int	go_path(char **args)
{
	char	*path;

	path = args[1];
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	set_value("OLDPWD", getcwd(NULL, 0));
	set_value("PWD", getcwd(NULL, 0));
	return (0);
}

int	ft_cd(char **args)
{
	int	status;

	status = 0;
	if (args[1] == NULL)
		go_home();
	else if (args[1][0] == '-' && args[1][1] == '\0')
		go_oldpwd();
	else
		status = go_path(args);
	return (status);
}
