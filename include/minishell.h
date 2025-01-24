/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:53:34 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/23 16:42:44 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"

# define WHITESPACE " /t/n/v/f/r"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_oper
{
	char	**cmd;
	int		num_cmd;
	int		ret_code;
}			t_oper;

typedef struct s_data
{
	char	*str;
	t_oper	pipe;
	t_oper	and;
	t_oper	or;
	t_oper	dir_input;			//
	t_oper	dir_output;			//
	t_oper	dir_app;			//
	t_oper	heredoc;			// could prob summarize all dir oper into one
	char	*final;
}			t_data;

char	**ft_split2(const char *s, const char *delim);
size_t	count_substr(const char *s, const char *delim);
void		externals(char **str);

#endif