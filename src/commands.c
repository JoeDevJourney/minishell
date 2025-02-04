/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/04 13:58:53 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @note **path needs freeing!  <---------------
 */
static char	*path_to_exec(char *name)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**path;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (printf("$PATH not set\n"), NULL);
	while (*path)
	{
		dir = opendir(*path);
		if (!dir)
			return (perror("opendir failed"), NULL);
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strncmp(name, entry->d_name, ft_strlen(entry->d_name)))
				return (closedir(dir), *path);
			entry = readdir(dir);
		}
		closedir (dir);
		path++;
	}
	return (NULL);
}

static int	exec_external(char **argv, char **envp)
{
	char	*direct;
	char	*full_path;

	// expansion_oper(argv);
	direct = ft_strjoin(path_to_exec(*argv), "/");
	full_path = ft_strjoin(direct, *argv);
	free(*argv);
	*argv = ft_strdup(full_path);
	if (execve(*argv, argv, envp) == -1)
		return (perror("execve failed"), errno);
	return (free(full_path), free(direct), 0);
}

char	*join_cmd(char **arr)
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
int	exec_command(char **str, t_data inp)
{
	char	**cmd;
	char	*input;
	int		res;
	int		*fd;

	// TODO: double quotes handling
	input = join_cmd(str);
	cmd = ft_split(input, ' ');

	while (*cmd)
		printf("'%s'\n", *cmd++);
	pause();

	fd = search_redir_oper(cmd);
	res = search_builtins(cmd, inp);
	if (res == -2)
		res = exec_external(cmd, inp.env);
	free_array (cmd);
	free (input);
	dup2(fd[1], fd[0]);
	close(fd[0]);
	free(fd);
	return (res);
}

/**
 * @brief Creates the child process for a single command
 */
int	handle_command(t_data inp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_command(inp.pipe.cmd, inp);
		exit (0);
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
		perror("Fork failed");
	return (0);
}

// cc commands.c -o commands functions.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c expansion_oper.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_memmove.c builtins/builtins.c -g -Wall -Werror -Wextra
// ./commands ls -l
// ./commands echo "This is a text"