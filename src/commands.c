/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 16:31:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	execute_external(char *cmd, char *argv[], char *envp[])
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, argv, envp) == -1)
		{
			perror("execve failed");
			return (errno);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	else
		perror("Fork failure");
	return (0);
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
		temp = ft_strjoin(*arr, " ");
		newline = ft_strjoin(line, temp);
		free(temp);
		free (line);
		line = newline;
		arr++;
	}
	temp = NULL;
	return (line);
}

static void	free_array(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
		free(*temp++);
	free (arr);
	arr = NULL;
}

/**
 * @brief Handles all execution, both externals and builtins
 * @param str command to be executed, broken down in tokens.
 * @note It can handle the command being a str or an array of str.
 */
int	execute_command(char **str, char **env)
{
	char	**input;
	char	*cmd;
	int		res;

	// TODO: double quotes handling
	cmd = join_cmd(str);
	input = ft_split(cmd, ' ');
	*input = ft_strjoin("/bin/", *input);
	expansion_oper(input);
	res = execute_external(*input, input, env);
	free_array (input);
	free (cmd);
	return (res);
}

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	execute_command(++argv, env);
// }
// cc commands.c -o commands ../include/libft/src/ft_strlen.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c expansion_oper.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_memmove.c -g -Wall -Werror -Wextra
// ./a.out ls -l
// ./execute_command echo "This is a text"