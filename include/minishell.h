/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:53:34 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/07 16:30:38 by jbrandt          ###   ########.fr       */
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
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <dirent.h>

typedef struct s_oper
{
	char	**cmd;
	int		num_cmd;
	int		ret_val;
}			t_oper;

typedef struct s_data
{
	char	*home_dir;
	char	**env;
	char	*str;
	t_oper	and;
	t_oper	or;
	t_oper	pipe;
	t_oper	redir;		
}			t_data;

//	Execution
int		exec_command(t_data inp);
int		handle_pipes(t_data inp);
int		handle_command(t_data inp);

//	Operators
void	expansion_oper(char **arr);
int		*search_redir_oper(t_data *inp);

//	Builtins
int		search_builtins(t_data inp);
int		exec_env(char **env);
int		exec_pwd(char **cmd);

//	Utilities
char	**ft_split2(const char *s, const char *delim);
size_t	count_substr(const char *s, const char *delim);
char	*join_cmd(char **arr);
void	free_array(char **arr);
void	*safe_malloc(size_t size);
char	*rwd(char *dir);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_write_error(const char *msg);
char	*get_home_dir(void);
char	*get_oldpwd_dir(void);
char	*get_target_dir(char **args);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
int		update_env_var(char **env, const char *name, const char *value);
int		update_pwd_vars(char **env, const char *oldpwd);
int		ft_cd(char **env, char **args);
int		ft_strcmp(const char *s1, const char *s2);
int		add_env_var(char **env, char *new_entry);
void	safe_free(void *ptr);
int		is_builtin(char *cmd);
int		execute_builtin(char **env, char **args);
int		ft_exit(char **args);
char	*get_target_dir(char **args);
int		is_valid_identifier(const char *str);
void	ft_arrfree(char **arr);
char	**ft_arrdup(char **arr, int size);
void	ft_swap(void *a, void *b, size_t size);

#endif