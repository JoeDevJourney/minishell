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

// static char	*path_to_exec(char *name)
// {
// 	struct dirent	*entry;
// 	DIR				*dir;
// 	char			**path;

// 	path = ft_split(getenv("PATH"), ':');
// 	if (!path)
// 	{
// 		printf("$PATH not set\n");
// 		return (NULL);
// 	}
// 	while (*path)
// 	{
// 		dir = opendir(*path);
// 		if (!dir)
// 			perror("opendir");
// 		else
// 		{
// 			entry = readdir(dir);
// 			while (entry)
// 			{
// 				if (!ft_strncmp(name, entry->d_name, ft_strlen(name)))
// 					return (*path);
// 				entry = readdir(dir);
// 			}
// 			closedir(dir);
// 		}
// 		path++;
// 	}
// 	// free
// 	return (NULL);
// }

static int	exec_external(char **argv, char **envp)
{
	// char	*exec;
	char	*temp;

	expansion_oper(argv);
	// exec = ft_strjoin(path_to_exec(*argv), "/");
	// temp = ft_strjoin(exec, *argv);
	// free(*argv);
	// *argv = ft_strdup(temp);
	temp = ft_strdup(*argv);
	free(*argv);
	*argv = ft_strjoin("/bin/", temp);
	if (execve(*argv, argv, envp) == -1)
	{
		perror("execve failed");
		return (errno);
	}
	// return(free(temp), free(exec), 0);
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
	// free(newline);	(?)
	return (line);
}

/**
 * @brief Handles all execution, both externals and builtins
 * @param str command to be executed, broken down in tokens.
 * @note It can handle the command being a str or an array of str.
 */
int	exec_command(char **str, char **env)
{
	char	**cmd;
	char	*input;
	int		res;

	// TODO: double quotes handling
	input = join_cmd(str);
	cmd = ft_split(input, ' ');
	res = search_builtins(cmd, env);  				//(cmd, env) ??
	if (res == -2)
		res = exec_external(cmd, env);
	free_array (cmd);
	free (input);
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
		exit (0);
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
// cc commands.c -o commands functions.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c expansion_oper.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_memmove.c builtins/builtins.c -g -Wall -Werror -Wextra
// ./commands ls -l
// ./commands echo "This is a text"