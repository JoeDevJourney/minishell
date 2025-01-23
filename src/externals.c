/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/23 15:40:20 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	execute_command(char *cmd, char *argv[], char *envp[])
{
	pid_t	pid;
	int		res;

	pid = fork();
	res = 0;
	if (pid == 0)
	{
		res = execve(cmd, argv, envp);
		exit(errno);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("Fork failure");
	return (res);
}

static char	*join_cmd(char **arr)
{
	char	*temp;
	char	*line;
	char	*newline;

	temp = NULL;
	newline = NULL;
	line = NULL;
	while (*arr)
	{
		temp = ft_strjoin(*arr++, " ");
		newline = ft_strjoin(line, temp);
		free(temp);
		free (line);
		line = newline;
	}
	return (line);
}

static void	free_array(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free (arr);
}

int	externals(char **str)
{
	char	**input;
	char	*cmd;
	int		res;

	cmd = join_cmd(str);
	input = ft_split(cmd, ' ');
	free(input[0]);
	*input = ft_strjoin("/bin/", *str);
	res = execute_command(*input, input, NULL);
	printf("%d\n", res);
	free_array (input);
	free (cmd);
	return (res);
}

	// cc externals.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c -g -Wall -Werror -Wextra
