/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:53:34 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/20 17:57:08 by dchrysov         ###   ########.fr       */
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
# include <dirent.h>

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}				t_env_var;

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
	char			*home_dir;
	char			**env;
	t_env_var		*nvp;
	char			*input;
	char			**command;
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
void	exec_command(t_data *inp);
void	handle_pipes(t_data *inp);
void	handle_command(t_data *inp);
void	exec_external(t_data inp);
int		exec_unset(char **cmd, char ***env);

//	Operators
void	expansion_oper(char **arr);
void	process_fds(t_data *inp);
void	parse_redir(t_data *inp);

//	Builtins
bool	search_builtins(t_data inp);
int		exec_builtin(t_data inp);
int		exec_env(char **env);
int		exec_pwd(char **cmd);
int		exec_exit(char *cmd);

//	Utilities
size_t	count_array_size(char **arr);
size_t	count_substr(const char *s, const char *delim);
char	**ft_split2(const char *s, const char *delim);
char	**add_to_array(char **arr, char *new_str);
char	*rwd(char *dir);
void	*safe_malloc(size_t size);
void	init_redir(t_data *inp);
void	free_array(char **arr);
void	free_redir(t_data *inp);
void	free_commands(t_data *inp);
void	free_array_fd(int **fd);
void	exit_with_error(char *msg, int ret_val);
void	print_data(t_data inp);

#endif