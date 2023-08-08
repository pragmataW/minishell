#include "../minishell.h"

static void	go_home(void)
{
	char	*path;
	char	*cwd;

	path = find_values(g_data.env, "HOME", NULL);
	cwd = getcwd(NULL, 0);
	set_value("OLDPWD", cwd);
	chdir(path);
	free(cwd);
	cwd = getcwd(NULL, 0);
	set_value("PWD", cwd);
	free(cwd);
	free(path);
}

static void	go_oldpwd(void)
{
	char	*path;
	char	*cwd;

	path = find_values(g_data.env, "OLDPWD", NULL);
	cwd = getcwd(NULL, 0);
	set_value("OLDPWD", cwd);
	free(cwd);
	chdir(path);
	cwd = getcwd(NULL, 0);
	set_value("PWD", cwd);
	free(cwd);
	free(path);
}

static int	go_path(char **args)
{
	char	*path;
	char	*cwd;

	path = args[1];
	cwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		free(cwd);
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	set_value("OLDPWD", cwd);
	free(cwd);
	cwd = getcwd(NULL, 0);
	set_value("PWD", cwd);
	free(cwd);
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
