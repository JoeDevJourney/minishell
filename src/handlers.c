/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/28 11:20:00 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	output(char **cmd, const char *file)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		externals(cmd);
	}
	else
		wait(NULL);
}

void	redir_oper(t_data *cmd, char *str)
{
	if (count_substr(str, "<") != 1)
	{
		cmd->dir_input.cmd = ft_split2(str, "<");
		cmd->dir_input.num_cmd = 2;
	}
	else if (count_substr(str, ">") == 1)
	{
		cmd->dir_output.cmd = ft_split2(str, ">");
		cmd->dir_output.num_cmd = 2;
		output(ft_split(cmd->dir_output.cmd[0], ' '), cmd->dir_output.cmd[1]);
	}
	else if (count_substr(str, ">>") == 1)
	{
		cmd->dir_app.cmd = ft_split2(str, ">>");
		cmd->dir_app.num_cmd = 2;
	}
	else
	{
		cmd->heredoc.cmd = ft_split2(str, "<<");
		cmd->heredoc.num_cmd = 2;
	}
}

// int main(void)
// {
//     const char *output_file = "output.txt";
//     char *cmd[] = {"cat", "-e", "../Makefile", NULL};
// 	// char *cmd[] = {"ls", "-la", NULL};
//     output(cmd, output_file);
//     return 0;
// }

// cc handlers.c externals.c parsing.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strnstr.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_memmove.c -g -Wall -Werror -Wextra