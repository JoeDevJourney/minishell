/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/17 17:56:11 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	out_oper(t_data *inp)
{
	char	**tok;
	int		fd;
	int		i;

	tok = ft_split2(*inp->pipe.cmd, ">");
	inp->out_op.cmd = ft_split(*tok, ' ');
	inp->out_op.num_cmd = str_count(*tok, ' ');
	i = 0;
	while (tok[++i])
	{
		fd = open(ft_strtrim(tok[i], " "),
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			free_array(tok);
			exit_with_error(ft_strtrim(tok[i], " "), 1);
		}
		if (!tok[i + 1])
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	free_array(tok);
}

static void	inp_oper(t_data *inp)
{
	inp->inp_op.fd[0] = STDIN_FILENO;
	inp->inp_op.fd[1] = open(*inp->inp_op.cmd++, O_RDONLY);
	if (inp->inp_op.fd[1] == -1)
		perror(*inp->inp_op.cmd);
	if (!*inp->inp_op.cmd)
		dup2(inp->inp_op.fd[1], inp->inp_op.fd[0]);
	close(inp->inp_op.fd[1]);
}

static void	app_oper(t_data *inp)
{
	char	**tok;
	int		fd;
	int		i;

	tok = ft_split2(*inp->pipe.cmd, ">>");
	inp->app_op.cmd = ft_split(*tok, ' ');
	inp->app_op.num_cmd = str_count(*tok, ' ');
	i = 0;
	while (tok[++i])
	{
		fd = open(ft_strtrim(tok[i], " "),
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			free_array(tok);
			exit_with_error(ft_strtrim(tok[i], " "), 1);
		}
		if (!tok[i + 1])
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	free_array(tok);
}

static void	hdoc_oper(t_data *inp)
{
	char	**tok;
	char	*input;
	int		fd;

	tok = ft_split2(*inp->pipe.cmd, "<<");
	inp->hdoc_op.cmd = ft_split(*tok, ' ');
	inp->hdoc_op.num_cmd = str_count(*tok, ' ');
	fd = open(ft_strjoin(inp->home_dir, "/src/heredoc"),
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline("heredoc> ");
		if (*input != '\0'
			&& !ft_strncmp(input, ft_strtrim(tok[1], " "), ft_strlen(input)))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
	}
	close(fd);
	fd = open(ft_strjoin(inp->home_dir, "/src/heredoc"), O_RDONLY);
	dup2(fd, STDIN_FILENO);
	return (free(input), close(fd), free_array(tok));
}

void	parse_redir(t_data *inp)
{
	process_fds(inp);
	// print_data(*inp);
	while (*inp->input)
	{
		if (*inp->input == '<')
		{
			if (++*inp->input == '<')
				hdoc_oper(inp);
			else
				inp_oper(inp);
		}
		else if (*inp->input == '>')
		{
			if (++*inp->input == '>')
				app_oper(inp);
			else
				out_oper(inp);
		}
		inp->input++;
	}
}

// cc redir_oper.c -o redir_oper commands.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c -Wall -Werror -Wextra
