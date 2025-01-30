/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   externals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/30 14:25:01 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	execute_command(char *cmd, char *argv[], char *envp[])
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

/**
 * @brief Executes all external commands (executables located at /bin/)
 * 
 * @paragraph str command to be executed, broken down in tokens.
 */
int	externals(char **str)
{
	char	**input;
	char	*cmd;
	int		res;

	res = 0;
	cmd = join_cmd(str);
	input = ft_split(cmd, ' ');
	*input = ft_strjoin("/bin/", *input);
	res = execute_command(*input, input, NULL);
	free_array (input);
	free (cmd);
	return (res);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	externals(++argv);
// }

	// cc externals.c -o externals ../include/libft/src/ft_strlen.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c -g -Wall -Werror -Wextra
	// ./a.out ls -l
	// ./externals echo "This is a text"