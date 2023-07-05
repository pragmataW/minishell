#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include "libft/libft.h"

typedef struct s_env
{
	char	**keys;
	char	**values;
	char	*tilda;
}			t_env;

typedef struct s_data
{
	t_env	*env;
	int		counter;
}				t_data;

extern t_data	data;

//! MAIN
void		free_list(t_list **list);
//! LEXER
t_list		**lexer(char *prompt, int i, int j, int end);
t_list		**trim_all(t_list **splited_str);
//! LEXER UTILS
void		allocator(char *ret, char *src, int len);
void		quotes_skipper(int *i, char *prompt);
int			command_len(char *cmd);
//! INIT_ENV
t_env		*env_variables(char **env, int env_count);
//! INIT_ENV UTILS
int			find_char(char *str, char c);
//!EXPANDER UTILS
void		expand_quote(t_list *iter, int *i, char *new_str, int *j);
void		expand_single_quote(t_list *iter, int *i, char *new_str, int *j);
void		expand_dollar(t_list *iter, int *i, char *new_str, int *j);
void	    tilda_extra(t_list *iter, int *i, char *new_str, int *k);
//! EXPANDER UTILS EXTRA
char		*find_values(t_env *env, char *kw);
char		*ft_str_realloc(char *str);
void		expand_normal(t_list *iter, int *i, char *new_str, int *j);
void		new_command(t_list *iter, char *str);
//! EXPANDER
static void	expand_tilda(t_list **splitted_str, int i, int k);
void		expander(t_list **splitted_str, char **env);
static void	expand_var(t_list **splitted_str, int i, int j);
#endif