/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/24 13:53:06 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Searches the $PATH directories for the exec
 * 
 * @param name Name of the executable
 */
static char	*path_to_exec(char *name)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**path;
	char			**ptr;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (perror("$PATH not set"), NULL);
	ptr = path;
	while (*ptr)
	{
		dir = opendir(*ptr);
		if (!dir)
			return (free_array(path), perror(*ptr), NULL);
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strncmp(name, entry->d_name, ft_strlen(entry->d_name)))
				return (closedir(dir), *ptr);
			entry = readdir(dir);
		}
		closedir (dir);
		ptr++;
	}
	return (free_array(path), NULL);				// <--- free_array() ?
}

/**
 * @brief Executes an external command
 */
void	exec_external(t_data inp)
{
	char	*dir;
	char	*full_path;

	dir = ft_strjoin(path_to_exec(*inp.command), "/");
	full_path = ft_strjoin(dir, *inp.command);
	free(*inp.command);
	*inp.command = ft_strdup(full_path);
	free(full_path);
	free(dir);
	if (execve(*inp.command, inp.command, inp.env) == -1)
		exit_with_error(*inp.command, errno);
}

/**
 * @brief Creates the child process for a single command
 */
int	fork_command(t_data *inp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_external(*inp);
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	else
		perror("Fork failed");
	return (0);
}

void	handle_command(t_data *inp)
{
	struct stat	info;

	if (strchr(*inp->command, '/'))
	{
		if (stat(*inp->command, &info) == 0 && S_ISDIR(info.st_mode))
			printf("%s: is a directory\n", *inp->command);
		else
			printf("%s: No such file or directory\n", *inp->command);
	}
	else
	{
		if (search_builtins(*inp))
			inp->ret_val = exec_builtin(inp->command, &inp->env);
		else if (path_to_exec(*inp->command))
			inp->ret_val = fork_command(inp);
		else
			printf("%s: command not found\n", *inp->command);
	}
}

/**
 * @brief Handles all execution, for both externals and builtins commands
 */
void	execute_command(t_data *inp)
{
	int			sfd[2];

	sfd[0] = dup(STDIN_FILENO);
	sfd[1] = dup(STDOUT_FILENO);
	if (inp->pipe.num_cmd != 1)
		handle_pipes(inp);
	else
	{
		if (process_fds(inp))					// quotes()
			handle_command(inp);
		else
			inp->ret_val = 1;
		free_redir(inp);
		free_commands(inp);
		init_redir(inp);
	}
	dup2(sfd[0], STDIN_FILENO);
	dup2(sfd[1], STDOUT_FILENO);
	close(sfd[0]);
	close(sfd[1]);
}
