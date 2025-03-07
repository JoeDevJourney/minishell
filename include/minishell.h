/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:38:05 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/07 12:01:20 by dchrysov         ###   ########.fr       */
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
# include <signal.h>

extern volatile sig_atomic_t g_signal;

typedef struct s_logical_op
{
	char	**cmd;
	int		num_cmd;
}			t_logical_op;

typedef struct s_redir_op
{
	char	**cmd;
	int		num_cmd;
	int		**fd;
}			t_redir_op;

typedef struct s_data
{
	pid_t			pid;
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
	int				ret_val;
}			t_data;

//	Execution
int				exec_pipes(t_data *inp);
void			parse_n_exec(t_data *inp);
void			exec_external(t_data inp);

//	Parsing/expansion
bool			process_fds(t_data *inp);
bool			hdoc_oper(t_data *inp);
void			parse_redir(t_data *inp);
void			parse_n_tokenize(t_data *inp);
void			parse_input(t_data *inp);
void			handle_quote(char **arr, char **env, char quote);
void			check_open_quotes(char **str);
void			expand_redir(t_data *inp);
void			expansion(char **str, t_data inp);

//	Builtins
bool			search_builtins(t_data inp);
int				exec_builtin(t_data *inp);
int				exec_env(char **env);
int				exec_unset(char **cmd, char ***env);
int				exec_pwd(char **cmd);
int				exec_exit(char *cmd);
int				exec_echo(char **str);
int				exec_export(t_data *inp);
int				exec_cd(t_data *inp);
char			*get_target_dir(t_data inp);
int				update_pwd_vars(char ***env, char *oldpwd);
int				update_env_var(char ***env, char *name, char *value);
char			*get_env_val(t_data inp, char *name);
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
char			*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char			*join_cmd(char **arr, char *del);

#endif
