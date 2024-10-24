/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelna <mabdelna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:53:15 by mabdelna          #+#    #+#             */
/*   Updated: 2024/10/02 12:05:37 by mabdelna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>

# define PROMPT "\e[38;5;111mminishell\033[34m$ \033[0m"

int						g_lock;

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_NL,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}						t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 125,
	ENO_NOT_FOUND = 127,
	ENO_EXEC_255 = 255
}						t_err_no;

typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}						t_ast_direction;

typedef struct s_err
{
	t_err_no			no;
	t_err_msg			msg;
	char				*cause;
}						t_err;

typedef struct s_path
{
	t_err				err;
	char				*path;
}						t_path;

typedef enum e_node_type
{
	N_PIPE,
	N_CMD
}						t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}						t_io_type;

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}						t_parse_err_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}						t_io_node;

typedef struct s_node
{
	t_node_type			type;
	t_io_node			*io_list;
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct s_parse_err
{
	t_parse_err_type	type;
	char				*str;
}						t_parse_err;

typedef struct s_minishell
{
	char				*line;
	t_token				*tokens;
	t_token				*curr_token;
	t_node				*ast;
	int					exit_s;
	t_parse_err			parse_err;
	int					stdin;
	int					stdout;
	char				**environ;
	t_env				*envlst;
	struct termios		original_term;
}						t_minishell;

int						ft_cd(t_minishell *minishell, char *path);
int						ft_echo(char **args);
char					*ft_get_envlst_val(t_minishell *minishell, char *key);
bool					ft_env_entry_exists(t_minishell *minishell, char *key);
void					ft_update_envlst(t_minishell *minishell, char *key,
							char *value, bool create);
char					*ft_extract_key(char *str);
char					*ft_extract_value(char *str);
void					ft_init_envlst(t_minishell *minishell);
int						ft_env(t_minishell *minishell);
void					ft_exit(t_minishell *minishell, char **args);
int						ft_check_key(char *str);
int						ft_export(t_minishell *minishell, char **argv);
int						ft_pwd(void);
int						ft_unset(t_minishell *minishell, char **args);
void					ft_clean(t_minishell *minishell);
int						ft_err_msg(t_err err);
int						ft_exec_builtin(t_minishell *minishell, char **args);
bool					ft_is_builtin(char *arg);
int						ft_out(t_io_node *io_list, int *status);
int						ft_in(t_io_node *io_list, int *status);
int						ft_append(t_io_node *io_list, int *status);
void					*ft_garbage_col(void *ptr, bool clean);
bool					ft_is_delimiter(char *delimiter, char *str);
int						ft_get_exit_status(int status);
int						ft_exec_node(t_minishell *minishell, t_node *tree,
							bool piped);
t_err					ft_check_exec(char *file, bool cmd);
t_err					ft_check_read(char *file);
t_err					ft_check_write(char *file);
int						ft_check_redirection(t_node *node);
void					ft_reset_stds(t_minishell *minishell, bool piped);
int						ft_exec_simple_cmd(t_minishell *minishell, t_node *node,
							bool piped);
t_path					ft_get_path(t_minishell *minishell, char *cmd);
void					ft_init_tree(t_minishell *minishell, t_node *node);
void					ft_heredoc(t_minishell *minishell, t_io_node *io,
							int p[2]);
bool					ft_is_valid_var_char(char c);
char					*ft_handle_normal_str(char *str, size_t *i);
char					*ft_handle_squotes(char *str, size_t *i);
char					*ft_handle_dquotes(t_minishell *minishell, char *str,
							size_t *i);
char					*ft_handle_dollar(t_minishell *minishell, char *str,
							size_t *i);
char					**ft_expand(t_minishell *minishell, char *str);
char					**ft_expander_split(char const *s);
char					*ft_strip_quotes(char *str);
void					ft_heredoc_expander(t_minishell *minishell, char *str,
							int fd);
void					ft_sigquit_handler(int num);
void					ft_init_signals(t_minishell *minishell);
void					ft_set_minishell(t_minishell *minishell);
t_minishell				*ft_get_minishell(void);
void					ft_clear_cmd_node(t_node *node);
void					ft_clear_ast(t_minishell *minishell, t_node **ast);
void					ft_set_parse_error(t_minishell *minishell,
							t_parse_err_type type);
void					ft_handle_parse_error(t_minishell *minishell);
t_node					*ft_get_simple_cmd(t_minishell *minishell);
t_io_type				ft_get_io_type(t_token_type type);
t_node					*ft_new_node(t_node_type type);
t_io_node				*ft_new_io_node(t_token_type type, char *value);
void					ft_append_io_node(t_io_node **lst, t_io_node *new);
void					ft_get_next_token(t_minishell *minishell);
bool					ft_curr_token_is_binop(t_minishell *minishell);
bool					ft_is_redir(t_token_type type);
t_node					*ft_expression(t_minishell *minishell);
t_node					*ft_parse(t_minishell *minishell);
int						ft_is_quote(char c);
t_token					*ft_tokenize_helper(t_minishell *minishell, char *line);
t_token					*ft_new_token(char *value, t_token_type type);
void					ft_token_list_add_back(t_token **lst,
							t_token *new_token);
void					ft_clear_token_list(t_token **lst);
int						ft_is_separator(char *s);
void					ft_skip_spaces(char **line);
bool					ft_skip_quotes(char *line, size_t *i);
void					ft_print_quote_err(t_minishell *minishell, char c);
t_token					*ft_tokenize(t_minishell *minishell);

#endif
