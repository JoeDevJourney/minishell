/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/26 18:00:16 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	out_oper(t_data *inp)
{
	static size_t	i;

	inp->out_op.fd = safe_malloc(3 * sizeof(int *));
	inp->out_op.fd[0] = safe_malloc(sizeof(int));
	inp->out_op.fd[1] = safe_malloc(sizeof(int));
	inp->out_op.fd[2] = NULL;
	*inp->out_op.fd[0] = STDOUT_FILENO;
	*inp->out_op.fd[1] = open(inp->out_op.cmd[i],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*inp->out_op.fd[1] == -1)
		return (perror(inp->out_op.cmd[i]), false);
	if (!inp->out_op.cmd[++i])
		dup2(*inp->out_op.fd[1], *inp->out_op.fd[0]);
	close(*inp->out_op.fd[1]);
	if (i == count_array_size(inp->out_op.cmd))
		i = 0;
	return (true);
}

static bool	inp_oper(t_data *inp)
{
	static size_t	i;

	inp->inp_op.fd = safe_malloc(3 * sizeof(int *));
	inp->inp_op.fd[0] = safe_malloc(sizeof(int));
	inp->inp_op.fd[1] = safe_malloc(sizeof(int));
	inp->inp_op.fd[2] = NULL;
	*inp->inp_op.fd[0] = STDIN_FILENO;
	*inp->inp_op.fd[1] = open(inp->inp_op.cmd[i], O_RDONLY);
	if (*inp->inp_op.fd[1] == -1)
		return (perror(inp->inp_op.cmd[i]), false);
	if (!inp->inp_op.cmd[++i])
		dup2(*inp->inp_op.fd[1], *inp->inp_op.fd[0]);
	close(*inp->inp_op.fd[1]);
	if (i == count_array_size(inp->inp_op.cmd))
		i = 0;
	return (true);
}

static bool	app_oper(t_data *inp)
{
	static size_t	i;

	inp->app_op.fd = safe_malloc(3 * sizeof(int *));
	inp->app_op.fd[0] = safe_malloc(sizeof(int));
	inp->app_op.fd[1] = safe_malloc(sizeof(int));
	inp->app_op.fd[2] = NULL;
	*inp->app_op.fd[0] = STDOUT_FILENO;
	*inp->app_op.fd[1] = open(inp->app_op.cmd[i],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*inp->app_op.fd[1] == -1)
		return (perror(inp->app_op.cmd[i]), false);
	if (!inp->app_op.cmd[++i])
		dup2(*inp->app_op.fd[1], *inp->app_op.fd[0]);
	close(*inp->app_op.fd[1]);
	if (i == count_array_size(inp->app_op.cmd))
		i = 0;
	return (true);
}

static bool	hdoc_oper(t_data *inp)
{
	static size_t	i;
	char			*input;
	char			*hdoc;

	hdoc = ft_strjoin(inp->home_dir, "/src/heredoc");
	inp->hdoc_op.fd = safe_malloc(3 * sizeof(int *));
	inp->hdoc_op.fd[0] = safe_malloc(sizeof(int));
	inp->hdoc_op.fd[1] = safe_malloc(sizeof(int));
	inp->hdoc_op.fd[2] = NULL;
	*inp->hdoc_op.fd[0] = STDIN_FILENO;
	*inp->hdoc_op.fd[1] = open(hdoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*inp->hdoc_op.fd[1] == -1)
		return (perror(inp->hdoc_op.cmd[i]), false);
	while (1)
	{
		input = readline("> ");
		if (*input != '\0'
			&& !ft_strncmp(input, inp->hdoc_op.cmd[i], ft_strlen(inp->input)))
			break ;
		ft_putendl_fd(input, *inp->hdoc_op.fd[1]);
		free(input);
	}
	close(*inp->hdoc_op.fd[1]);
	*inp->hdoc_op.fd[1] = open(hdoc, O_RDONLY);
	if (!inp->hdoc_op.cmd[++i])
		dup2(*inp->hdoc_op.fd[1], *inp->hdoc_op.fd[0]);
	close(*inp->hdoc_op.fd[1]);
	free(input);
	free(hdoc);
	if (i == count_array_size(inp->hdoc_op.cmd))
		i = 0;
	return (true);
}

/**
 * @brief Takes the (char *)inp->input and executes the appropriate redirection
 * based on the (char **)inp->command 
 * 
 * @note In all the individual redir functions, fd[0] is for the std fd and
 * fd[1] is the redirected one. 
 * 
 * @returns 1 in case of valid redir, 0 otherwise 
 */
bool	process_fds(t_data *inp)
{
	int		i;
	bool	res;

	parse_redir(inp);

//execute quotes only for the redirection arrays.

	print_data(*inp);
	i = -1;
	res = true;
	while (inp->input[++i] && res)
	{
		if (inp->input[i] == '<')
		{
			if (inp->input[++i] == '<')
				res = hdoc_oper(inp);
			else
				res = inp_oper(inp);
		}
		else if (inp->input[i] == '>')
		{
			if (inp->input[++i] == '>')
				res = app_oper(inp);
			else
				res = out_oper(inp);
		}
	}
	return (res);
}

// cc redir_oper.c -o redir_oper commands.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c -Wall -Werror -Wextra
