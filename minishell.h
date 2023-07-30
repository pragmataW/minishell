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
# include <sys/wait.h>
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

typedef struct s_table
{
	char			*cmd_path;
	char			**full_cmd;
	int				infile;
	int				outfile;
	struct s_table	*next;
}				t_table;

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
void		tilda_extra(t_list *iter, int *i, char *new_str, int *k);
//! EXPANDER UTILS EXTRA
char		*find_values(t_env *env, char *kw);
char		*ft_str_realloc(char *str);
void		expand_normal(t_list *iter, int *i, char *new_str, int *j);
void		new_command(t_list *iter, char *str);
//! EXPANDER
void		expander(t_list **splitted_str, char **env);
//! PARSER UTILS
void		table_add_back(t_table **lst, t_table *new);
t_table		*table_last(t_table *lst);
t_table		*table_new(void);
//! FILLNODE
int			node_counter(t_list *list);
t_table		**fill_node(t_list **list, int i);
#endif