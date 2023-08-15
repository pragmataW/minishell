/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yciftci <yciftci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:58:48 by yciftci           #+#    #+#             */
/*   Updated: 2023/08/15 17:25:21 by yciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/ioctl.h>
# include "libft/libft.h"

# define T "🥵minishell\033[38;2;243;222;186m⤵\033[0m\033[0m\033[38;2;243;222;186m"
# define PWD_COLOR "\033[0m\n\033[1;31m[\033[0m\033[38;2;243;222;186m"
# define RED "\033[1;31m"
# define LAST_TXT "\033[0m\033[1;31m]->\033[0m"
# define CLEAR_TERM "\x1b[2J"
# define RESET_CURSOR "\x1b[H"

typedef struct s_env
{
	char	**keys;
	char	**values;
	char	*tilda;
}			t_env;

typedef struct s_table
{
	char			*cmd_path;
	char			**full_cmd;
	int				infile;
	int				outfile;
	struct s_table	*next;
}				t_table;

typedef struct s_data
{
	t_env			*env;
	struct s_table	**cmd_table;
	t_list			**splitted_str;
	int				**pipes;
	char			*heredoc_path;
	int				process_count;
	int				counter;
	int				status;
	int				heredoc;
	int				err;
}				t_data;

extern t_data	g_data;

//!MINISHELL UTILS
char		*get_input(void);
//! LEXER
t_list		**lexer(char *prompt, int i, int end);
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
char		*find_values(t_env *env, char *kw, int *index);
char		*ft_str_realloc(char *str);
void		expand_normal(t_list *iter, int *i, char *new_str, int *j);
void		new_command(t_list *iter, char *str);
//! EXPANDER
void		expander(t_list **splitted_str);
//! PARSER UTILS
void		table_add_back(t_table **lst, t_table *new);
t_table		*table_last(t_table *lst);
char		*find_path(char *path, char *command);
t_table		*table_new(char *content);
//! EXPAND_CMD
int			is_builtin(char *cmd);
void		expand_cmd(t_table **table, int i);
void		expand_binary(t_table *node);
//! FILLNODE
t_table		**fill_node(t_list **list, int i);
//! FIND_REDIREC
void		find_redirec(t_table **root);
//! FIND_REDIREC_UTILS
void		terminate_command(t_table *iter);
void		set_fd(t_table *iter, int i, int fd, char opt);
char		*open_path(void);
void		get_heredoc(int fd, char *input, int id);
void		set_heredoc_fd(t_table *iter, int i, int fd);
//! PARSER
void		parser(t_list **expanded_str);
//!EXECUTER
void		executer(int i, int j);
//! EXECUTER UTILS
int			process_counter(t_table **cmd_table);
int			**create_pipes(int process_count);
//! FD_DUPS
void		single_exec(t_table *iter);
void		dup_first(t_table *iter, int **fd);
void		dup_last(t_table *iter, int **fd, int pc);
void		dup_mids(t_table *iter, int **fd, int j);
void		close_main_fd(int **fd, int *j, int *i, int pc);
//! BUILT-IN
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_env(void);
int			ft_unset(char **args, int i);
int			ft_export(char **args);
//! BUILD-IN2
int			ft_cd(char **args);
//! BUILT-IN EXECV
void		builtin_execv(t_table *node);
//! BUILT-IN UTILS
int			is_exportable(char *var);
int			matrix_size(char **matrix);
char		**resize_matrix(char	**matrix);
void		export_keywords(char *add, int i);
//! BUILT-IN UTILS2
void		export_value(char *add);
void		delete_value(char *delete);
void		set_value(char *add, char *value);
//! SIGNALS
void		signals_control(void);
void		heredoc_sig(int sig);
//! ERROR_UTILS
void		parse_error(t_table *iter);
void		command_not_found(void);
int			quote_check(char *prompt, int i);
//! ERROR_UTILS2
void		pipe_syntax_check(t_list **lexed_str);
void		redirec_syntax_check(t_list **lexed_str);
int			is_full_space(char *prompt);
//! ERRORS
void		errors(t_list **lexed_str, char *prompt);
//! FREE
void		free_list(t_list **list, char *prompt);
void		free_parsed(t_table **parsed);
void		free_matrix(char **matrix);
void		free_fd(int **fd);
void		free_global(char opt);
#endif
