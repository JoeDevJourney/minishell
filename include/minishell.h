/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:38:05 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 20:56:17 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\033[31m"
# define GRN "\033[32m"
# define YEL "\033[33m"
# define BLUE "\033[34m"
# define RST "\033[0m"

# include "libft/include/libft.h"
# include "getnextline/get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_redir_op
{
	char	**cmd;
	int		num_cmd;
	int		**fd;
}			t_redir_op;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_data
{
	pid_t			pid;
	char			*home_dir;
	t_env			*env;
	char			*input;
	char			*cmd;
	char			**tok;
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
int				exec_command(t_data *inp, bool pipe_flag, char **env);
int				main(int argc, char **argv, char **env);

//	Parsing/expansion
bool			process_fds(t_data *inp);
bool			hdoc_oper(t_data *inp);
bool			parse_input(t_data *inp);
bool			expand_redir(t_data *inp);
void			parse_redir(t_data *inp);
void			check_open_quotes(char **str);
void			expansion(char **str, t_data inp);

//	Builtins
bool			search_builtins(t_data inp);
int				exec_builtin(t_data *inp, char **env);
int				exec_env(t_env *env);
int				exec_unset(char **cmd, t_env **head);
int				exec_pwd(t_data inp);
int				exec_exit(t_data *inp, char **env);
int				exec_echo(char **str);
int				exec_export(t_data *inp);
int				exec_cd(t_data *inp);
int				update_env_var(t_env **head, char *name, char *value);
char			*get_env_val(t_data inp, char *name);
char			*get_target_dir(t_data inp);
void			dupl_env(t_env **head, char **env);
void			free_env_list(t_env *head);
t_env			*new_env_node(char *env_var);

//	Utilities
size_t			count_array_size(char **arr);
void			*safe_malloc(size_t size);
void			init_redir(t_data *inp);
void			free_array(char ***arr, int size);
void			free_redir(t_data *inp);
void			free_commands(t_data *inp);
void			free_array_fd(int **fd);
void			exit_with_error(char *msg, int ret_val);
void			print_data(t_data inp);
char			**ft_split2(const char *s, const char *delim);
char			*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char			*join_cmd(char **arr, char *del);
int				restart_minishell(t_data *inp);
void			setup_signals(bool is_child);
char			*ft_strjoin_free(char **s1, char *s2);
void			parent_signal(int sig);
void			child_signal(int sig);
int				handle_signal_status(int status);
char			**list_to_array(t_env *head);
void			write_to_fd(char **input, t_data *inp, int i);
int				count_delim(char *str, char *delim);
bool			check_inv_filename(t_data *inp);
int				count_oper(char *str, char oper, bool next);
void			check_quote(char c, bool *open_sq, bool *open_dq);
char			*build_prompt(t_data *inp);
bool			setup_heredoc_fd(t_data *inp, char **hdoc, size_t i);
void			exit_free(t_data *inp);
void			find_dir_exec(const char *dirpath, const char *exec, \
				char **path);
int				parse_n_flag(char **arr, bool *nl_flag);
void			free_struct(t_data *inp, bool pipe_flag);

#endif
