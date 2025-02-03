/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:53:34 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/03 13:07:26 by jbrandt          ###   ########.fr       */
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
}			t_data;

char	**ft_split2(const char *s, const char *delim);
size_t	count_substr(const char *s, const char *delim);
int		externals(char **str);
int		exec_pipes(int num, char **cmd);
void	*safe_malloc(size_t size);
char	*relative_wd(char *dir);
void	expansion_oper(char **arr);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_write_error(const char *msg);
char	*get_home_dir(void);
char	*get_oldpwd_dir(void);
char	*get_target_dir(char **args);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
int		update_env_var(const char *name, const char *value);
int		update_pwd_vars(const char *oldpwd);
int		ft_cd(char **args);
int		ft_strcmp(const char *s1, const char *s2);
int		add_env_var(char *new_entry);

#endif