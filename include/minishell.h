/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:53:34 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/10 19:59:22 by dchrysov         ###   ########.fr       */
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
	int		ret_val;
}			t_data;

//	Execution
void	exec_command(t_data inp);
int		handle_pipes(t_data *inp);
int		handle_command(t_data *inp);

//	Operators
void	expansion_oper(char **arr);
void	search_redir_oper(t_data *inp);

//	Builtins
void	search_builtins(t_data inp);
void	exec_env(char **env);
void	exec_pwd(char **cmd);

//	Utilities
size_t	count_substr(const char *s, const char *delim);
char	**ft_split2(const char *s, const char *delim);
char	*join_cmd(char **arr);
void	exit_with_error(char *msg, int ret_val);
void	free_array(char **arr);
void	*safe_malloc(size_t size);
char	*rwd(char *dir);

#endif