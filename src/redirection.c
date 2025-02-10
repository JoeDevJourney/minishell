/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/10 12:31:56 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	out_oper(t_data *inp)
{
	char	**tok;
	int		fd;
	int		i;

	tok = ft_split2(*inp->pipe.cmd, ">");
	inp->redir.cmd = ft_split(*tok, ' ');
	inp->redir.num_cmd = str_count(*tok, ' ');
	i = 0;
	while (tok[++i])
	{
		fd = open(ft_strtrim(tok[i], " "),
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(ft_strtrim(tok[i], " "));
			free_array(tok);
			exit(1);
		}
		if (!tok[i + 1])
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	free_array(tok);
}

static void	inp_oper(t_data *inp)
{
	char	**tok;
	int		fd;
	int		i;

	tok = ft_split(*inp->pipe.cmd, '<');
	inp->redir.cmd = ft_split(*tok, ' ');
	inp->redir.num_cmd = str_count(*tok, ' ');
	i = 0;
	while (tok[++i])
	{
		fd = open(ft_strtrim(tok[i], " "), O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strtrim(tok[i], " "));
			free_array(tok);
			exit(1);
		}
		if (!tok[i + 1])
			dup2(fd, STDIN_FILENO);
		close(fd);
	}
	free_array(tok);
}

static void	app_oper(t_data *inp)
{
	char	**tok;
	int		fd;
	int		i;

	tok = ft_split2(*inp->pipe.cmd, ">>");
	inp->redir.cmd = ft_split(*tok, ' ');
	inp->redir.num_cmd = str_count(*tok, ' ');
	i = 0;
	while (tok[++i])
	{
		fd = open(ft_strtrim(tok[i], " "),
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror(ft_strtrim(tok[i], " "));
			free_array(tok);
			exit(1);
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
	inp->redir.cmd = ft_split(*tok, ' ');
	inp->redir.num_cmd = str_count(*tok, ' ');
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

void	search_redir_oper(t_data *inp)
{
	if (ft_strnstr(*inp->pipe.cmd, "<<", ft_strlen(*inp->pipe.cmd)))
		hdoc_oper(inp);
	else if (ft_strnstr(*inp->pipe.cmd, "<", ft_strlen(*inp->pipe.cmd)))
		inp_oper(inp);
	else if (ft_strnstr(*inp->pipe.cmd, ">>", ft_strlen(*inp->pipe.cmd)))
		app_oper(inp);
	else if (ft_strnstr(*inp->pipe.cmd, ">", ft_strlen(*inp->pipe.cmd)))
		out_oper(inp);
	else
	{
		inp->redir.cmd = ft_split(*inp->pipe.cmd, ' ');
		inp->redir.num_cmd = str_count(*inp->pipe.cmd, ' ');
	}
}

// cc redir_oper.c -o redir_oper commands.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c -Wall -Werror -Wextra