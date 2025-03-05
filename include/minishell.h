/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/05 14:51:44 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITESPACE " /t/n/v/f/r"
# define RED "\033[31m"
# define GRN "\033[32m"
# define YEL "\033[33m"
# define BLUE "\033[34m"
# define RST "\033[0m"

# include "libft/include/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>

typedef struct s_logical_op
{
	char	**cmd;
	int		num_cmd;
}			t_logical_op;

typedef struct s_oper
{
	char	**cmd;
	int		num_cmd;
	int		ret_val;
}			t_oper;

typedef struct s_redir_op
{
	char	**cmd;
	int		num_cmd;
	int		**fd;
}			t_redir_op;

typedef struct s_quote_state
{
	bool	sq;
	bool	dq;
	bool	escape;
	bool	sq_closed;
	bool	dq_closed;
}	t_quote_state;

typedef struct s_data
{
	char			*home_dir;
	char			**env;
	char			*cmd;
	char			**tok;
	t_logical_op	and;
	t_logical_op	or;
	t_redir_op		pipe;
	t_redir_op		inp_op;
	t_redir_op		out_op;
	t_redir_op		app_op;
	t_redir_op		hdoc_op;
	t_quote_state	quotes;
	int				ret_val;
	t_oper			redir;
}			t_data;

typedef struct s_split_state
{
	bool			sq;
	bool			dq;
	bool			escape;
	char			*start;
	char			*ptr;
	t_quote_state	quotes;
}	t_split_state;

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;


//	Execution
int				exec_pipes(t_data *inp);
void			parse_n_exec(t_data *inp);
void			exec_external(t_data inp);

//	Operators
bool			process_fds(t_data *inp);
void			parse_redir(t_data *inp);
void			parse_logic(t_data *inp);
void			parse_command(t_data *inp);
void			handle_quote(char **arr, char **env, char quote);
void			check_open_quotes(char **str, char quote);
void			expand_redir(t_data *inp);
void			expansion(char **str, char **env);
void			expnd_quotes(char **str, char ***env,
					void (*f)(char **, char ***));

//	Builtins
bool			search_builtins(t_data inp);
int				exec_builtin(t_data *inp);
int				exec_env(char **env);
int				exec_unset(char **cmd, char ***env);
int				exec_pwd(char **cmd);
int				exec_exit(char *cmd);
int				exec_echo(char **str);
int				is_valid_identifier(const char *str);
char			**ft_arrdup(char **arr, int size);
void			ft_arrfree(char **arr);
void			ft_swap(void *a, void *b, size_t size);
int				ft_export(char *cmd, char ***env);
int				ft_cd(char ***env, char **args);
char			*create_env_entry(const char *name, const char *value);
int				replace_env_var(char **env, const char *name, char *new_entry);
int				update_env_var(char ***env, const char *name, \
				const char *value);
char			*get_home_dir(char **env);
char			*get_oldpwd_dir(char **env);
int				update_pwd_vars(char ***env, const char *oldpwd);
int				add_env_var(char ***env, char *new_entry);
char			*get_target_dir(char **args, char **env);
char			*get_env_val(char **env, char *name);
void			dupl_env(char ***arr, char **env);

//	Utilities
size_t			count_array_size(char **arr);
size_t			count_substr(const char *s, const char *delim);
bool			valid_oper(char **str, char *del);
char			**ft_split2(const char *s, const char *delim);
void			*safe_malloc(size_t size);
void			init_redir(t_data *inp);
void			free_array(char **arr);
void			free_redir(t_data *inp);
void			free_commands(t_data *inp);
void			free_array_fd(int **fd);
void			exit_with_error(char *msg, int ret_val);
void			print_data(t_data inp);
int				ft_strcmp(const char *s1, const char *s2);
int				is_valid_identifier(const char *str);
char			*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char			*join_cmd(char **arr, char *del);

// Quotes Utils
void			add_command(t_list **list, const char *start, const char *end);
char			*ft_strncpy(char *dst, const char *src, size_t len);

#endif
