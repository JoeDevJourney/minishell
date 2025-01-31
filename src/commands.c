/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 19:30:52 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_external(char *cmd, char *argv[], char *envp[])
{
	if (execve(cmd, argv, envp) == -1)
	{
		perror("execve failed");
		return (errno);
	}
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

/**
 * @brief Handles all execution, both externals and builtins
 * @param str command to be executed, broken down in tokens.
 * @note It can handle the command being a str or an array of str.
 */
int	exec_command(char **str, char **env)
{
	char	**input;
	char	*cmd;
	int		res;

	// TODO: double quotes handling
	res = 0;
	cmd = join_cmd(str);
	input = ft_split(cmd, ' ');
	// res = exec_builtins(input)
	// or res = exec_external()
	if (!strncmp(*input, "env", 3))
		exec_env(env);
	else
	{
		expansion_oper(input);							// This should go in the handling functions for extern and built 
		*input = ft_strjoin("/bin/", *input);
		res = exec_external(*input, input, env);
		free_array (input);
		free (cmd);
	}
	return (res);
}

int	fork_command(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_command(cmd, env);
		perror("exec_command failed");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(&status);
		if(WIFEXITED(status))
			return(WEXITSTATUS(status));
		else
			return (-1);
	}
	else
		perror("Fork failed");
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	exec_command(++argv, env);
// }
// cc commands.c -o commands ../include/libft/src/ft_strlen.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c expansion_oper.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_memmove.c -g -Wall -Werror -Wextra
// ./a.out ls -l
// ./exec_command echo "This is a text"