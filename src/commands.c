/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/05 13:31:34 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @note **path needs freeing!(?)  <---------------
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

static int	exec_external(t_data inp)
{
	char	*direct;
	char	*full_path;

	// expansion_oper(argv);
	direct = ft_strjoin(path_to_exec(*inp.redir.cmd), "/");
	full_path = ft_strjoin(direct, *inp.redir.cmd);
	free(*inp.redir.cmd);
	*inp.redir.cmd = ft_strdup(full_path);
	if (execve(*inp.redir.cmd, inp.redir.cmd, inp.env) == -1)
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
	fd = search_redir_oper(cmd, &inp);
	res = search_builtins(inp);
	if (res == -2)
		res = exec_external(inp);
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

// int	main(int argc, char **argv, char **env)
// {
// 	t_data	inp;

// 	(void)argc;
// 	(void)argv;
// 	inp.env = env;
// 	inp.home_dir = ft_strjoin(getenv("PWD"), "/..");
// 	inp.pipe.cmd = malloc(2 * sizeof(char *));
// 	inp.pipe.cmd[0] = ft_strdup("cat -e main.c");
// 	inp.pipe.cmd[1] = NULL;
// 	exec_command(inp.pipe.cmd, inp);
// 	// handle_command(inp);
// 	free_array(inp.pipe.cmd);
// 	free(inp.home_dir);
// }
// cc commands.c -o commands functions.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c redir_oper.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_memmove.c ../include/libft/src/ft_strtrim.c builtins/*.c -g -Wall -Werror -Wextra
