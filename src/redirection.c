/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/19 17:19:38 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	out_oper(t_data *inp)
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
		perror(inp->out_op.cmd[i]);
	if (!inp->out_op.cmd[++i])
		dup2(*inp->out_op.fd[1], *inp->out_op.fd[0]);
	close(*inp->out_op.fd[1]);
	if (i == count_array_size(inp->out_op.cmd))
		i = 0;
}

static void	inp_oper(t_data *inp)
{
	static size_t	i;

	inp->inp_op.fd = safe_malloc(3 * sizeof(int *));
	inp->inp_op.fd[0] = safe_malloc(sizeof(int));
	inp->inp_op.fd[1] = safe_malloc(sizeof(int));
	inp->inp_op.fd[2] = NULL;
	*inp->inp_op.fd[0] = STDIN_FILENO;
	*inp->inp_op.fd[1] = open(inp->inp_op.cmd[i], O_RDONLY);
	if (*inp->inp_op.fd[1] == -1)
		perror(inp->inp_op.cmd[i]);
	if (!inp->inp_op.cmd[++i])
		dup2(*inp->inp_op.fd[1], *inp->inp_op.fd[0]);
	close(*inp->inp_op.fd[1]);
	if (i == count_array_size(inp->inp_op.cmd))
		i = 0;
}

static void	app_oper(t_data *inp)
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
		perror(inp->app_op.cmd[i]);
	if (!inp->app_op.cmd[++i])
		dup2(*inp->app_op.fd[1], *inp->app_op.fd[0]);
	close(*inp->app_op.fd[1]);
	if (i == count_array_size(inp->app_op.cmd))
		i = 0;
}

static void	hdoc_oper(t_data *inp)
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
		perror(inp->hdoc_op.cmd[i]);
	while (1)
	{
		input = readline("heredoc> ");
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
}

void	parse_redir(t_data *inp)
{
	int	i;

	process_fds(inp);
	i = -1;
	while (inp->input[++i] && !errno)
	{
		if (inp->input[i] == '<')
		{
			if (inp->input[++i] == '<')
				hdoc_oper(inp);
			else
				inp_oper(inp);
		}
		else if (inp->input[i] == '>')
		{
			if (inp->input[++i] == '>')
				app_oper(inp);
			else
				out_oper(inp);
		}
	}
}

// cc redir_oper.c -o redir_oper commands.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c -Wall -Werror -Wextra
