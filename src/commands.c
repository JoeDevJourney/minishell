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

static char	*path_to_exec(char *name)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**path;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
	{
		printf("$PATH not set\n");
		return (NULL);
	}
	while (*path)
	{
		dir = opendir(*path);
		if (!dir)
			perror("opendir");
		else
		{
			entry = readdir(dir);
			while (entry)
			{
				if (!ft_strncmp(name, entry->d_name, ft_strlen(name)))
					return (*path);
				entry = readdir(dir);
			}
			closedir(dir);
		}
		path++;
	}
	// free
	return (NULL);
}

static int	exec_external(char **argv, char **envp)
{
	char	*exec;
	char	*temp;

	expansion_oper(argv);
	exec = ft_strjoin(path_to_exec(*argv), "/");
	temp = ft_strjoin(exec, *argv);
	free(*argv);
	*argv = ft_strdup(temp);
	if (execve(*argv, argv, envp) == -1)
	{
		perror("execve failed");
		return (errno);
	}
	return (free(exec), free(temp), 0);
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
	cmd = join_cmd(str);
	input = ft_split(cmd, ' ');
	if (!strncmp(*input, "env", 3))
		// res = exec_builtins(input)
		res = exec_env(env);
	else
		// or res = exec_external()
		res = exec_external(input, env);
	free_array (input);
	free (cmd);
	return (res);
}

int	fork_command(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_command(cmd, env);
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