/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:53:34 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/03 19:05:33 by dchrysov         ###   ########.fr       */
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
	char	*str;
	t_oper	pipe;
	t_oper	and;
	t_oper	or;
	t_oper	dir_input;			//
	t_oper	dir_output;			//
	t_oper	heredoc;			// could prob summarize all dir oper into one
	t_oper	dir_app;			//
	char	**env;
	char	*home_dir;
}			t_data;

//	Execution
int		exec_command(char **str, t_data inp);
int		exec_pipes(t_data inp);
int		fork_command(t_data inp);

//	Operators
void	expansion_oper(char **arr);
int		*search_redir_oper(char **cmd);

//	Builtins
int		search_builtins(char **cmd, t_data inp);
int		exec_env(char **env);
int		exec_pwd(char **cmd);

//	Utilities
char	**ft_split2(const char *s, const char *delim);
size_t	count_substr(const char *s, const char *delim);
char	*join_cmd(char **arr);
void	free_array(char **arr);
void	*safe_malloc(size_t size);
char	*rwd(char *dir);

#endif