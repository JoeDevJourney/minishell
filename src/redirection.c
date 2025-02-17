/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/17 20:01:51 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	out_oper(t_data *inp)
{
	inp->out_op.fd[0] = STDOUT_FILENO;
	inp->out_op.fd[1] = open(*inp->out_op.cmd,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inp->out_op.fd[1] == -1)
		perror(*inp->out_op.cmd);
	if (!*++inp->out_op.cmd)
		dup2(inp->out_op.fd[1], inp->out_op.fd[0]);
	close(inp->out_op.fd[1]);
}

static void	inp_oper(t_data *inp)
{
	inp->inp_op.fd[0] = STDIN_FILENO;
	inp->inp_op.fd[1] = open(*inp->inp_op.cmd, O_RDONLY);
	if (inp->inp_op.fd[1] == -1)
		perror(*inp->inp_op.cmd);
	if (!*++inp->inp_op.cmd)
		dup2(inp->inp_op.fd[1], inp->inp_op.fd[0]);
	close(inp->inp_op.fd[1]);
}

static void	app_oper(t_data *inp)
{
	inp->app_op.fd[0] = STDOUT_FILENO;
	inp->app_op.fd[1] = open(*inp->app_op.cmd,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (inp->app_op.fd[1] == -1)
		perror(*inp->app_op.cmd);
	if (!*++inp->app_op.cmd)
		dup2(inp->app_op.fd[1], inp->app_op.fd[0]);
	close(inp->app_op.fd[1]);
}

static void	hdoc_oper(t_data *inp)
{
	char	*input;
	char	*hdoc;

	hdoc = ft_strjoin(inp->home_dir, "/src/heredoc");
	inp->hdoc_op.fd[0] = STDIN_FILENO;
	inp->hdoc_op.fd[1] = open(hdoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inp->hdoc_op.fd[1] == -1)
		perror(*inp->hdoc_op.cmd);
	while (1)
	{
		input = readline("heredoc> ");
		if (*input != '\0'
			&& !ft_strncmp(input, *inp->hdoc_op.cmd, ft_strlen(inp->input)))
			break ;
		ft_putendl_fd(input, inp->hdoc_op.fd[1]);
		free(input);
	}
	close(inp->hdoc_op.fd[1]);
	inp->hdoc_op.fd[1] = open(hdoc, O_RDONLY);
	if (!*++inp->hdoc_op.cmd)
		dup2(inp->hdoc_op.fd[1], inp->hdoc_op.fd[0]);
	close(inp->hdoc_op.fd[1]);
	free(input);
	free(hdoc);
}

void	parse_redir(t_data *inp)
{
	process_fds(inp);
	// print_data(*inp);
	while (*inp->input)
	{
		if (*inp->input == '<')
		{
			if (*(++inp->input) == '<')
				hdoc_oper(inp);
			else
				inp_oper(inp);
		}
		else if (*inp->input == '>')
		{
			if (*(++inp->input) == '>')
				app_oper(inp);
			else
				out_oper(inp);
		}
		inp->input++;
	}
}

// cc redir_oper.c -o redir_oper commands.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c -Wall -Werror -Wextra
