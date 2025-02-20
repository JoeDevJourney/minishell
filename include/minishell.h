/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/20 18:54:24 by jbrandt          ###   ########.fr       */
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
# include <string.h>
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

typedef struct s_data
{
	char			*home_dir;
	char			**env;
	char			*str;
	char			*input;
	char			**command;
	const char		**pipe_cmd;
	t_logical_op	and;
	t_logical_op	or;
	t_redir_op		pipe;
	t_redir_op		inp_op;
	t_redir_op		out_op;
	t_redir_op		app_op;
	t_redir_op		hdoc_op;
	int				ret_val;
	t_oper			redir;
}			t_data;
typedef struct s_quote_state
{
	bool	sq;
	bool	dq;
	bool	escape;
}	t_quote_state;

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
void			exec_command(t_data *inp);
void			handle_pipes(t_data *inp);
void			handle_command(t_data *inp);
void			exec_external(t_data inp);

//	Operators
void			expansion_oper(char **arr);
void			process_fds(t_data *inp);
void			parse_redir(t_data *inp);

//	Builtins
bool			search_builtins(t_data inp);
int				exec_builtin(char **cmd, char **env);
int				exec_env(char **env);
int				exec_pwd(char **cmd);
int				exec_exit(char *cmd);
int				is_valid_identifier(const char *str);
char			**ft_arrdup(char **arr, int size);
void			ft_arrfree(char **arr);
void			ft_swap(void *a, void *b, size_t size);
int				ft_export(char **env, char **args);
int				ft_cd(char **env, char **args);
char			*create_env_entry(const char *name, const char *value);
int				replace_env_var(char **env, const char *name, char *new_entry);
int				update_env_var(char **env, const char *name, const char *value);
void			ft_write_error(const char *msg);
char			*get_home_dir(void);
char			*get_oldpwd_dir(void);
int				update_pwd_vars(char **env, const char *oldpwd);
int				add_env_var(char **env, char *new_entry);
char			*get_target_dir(char **args);


//	Utilities
size_t			count_array_size(char **arr);
size_t			count_substr(const char *s, const char *delim);
char			**ft_split2(const char *s, const char *delim);
char			**add_to_array(char **arr, char *new_str);
char			*join_cmd(char **arr);
char			*rwd(char *dir);
void			*safe_malloc(size_t size);
void			init_redir(t_data *inp);
void			free_array(char **arr);
void			free_redir(t_data *inp);
void			free_commands(t_data *inp);
void			free_array_fd(int **fd);
void			exit_with_error(char *msg, int ret_val);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strcat(char *dest, const char *src);
void			safe_free(void *ptr);

void			print_data(t_data inp);
// Quotes Utils
void			free_list(t_list *list);
void			add_command(t_list **list, const char *start, const char *end);
t_quote_state	init_quote_state(void);
unsigned long	ft_strlen(const char str[]);
char			*ft_strncpy(char *dst, const char *src, size_t len);
// Quotes
bool			check_quotes(const char *input);
void			handle_escape(const char **input, char **dst, \
				t_quote_state *state);
void			handle_quotes(const char **input, char **dst, \
				t_quote_state *state);
void			process_quotes(t_data	*inp);

#endif

// search for the $ sign in getenv and parse the word to it to the getenv and process it.
// look up if the quote is closed or not.
// search for the quotes and find out if its double or single and if there is a dollar sign inside.