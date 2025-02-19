/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/19 16:18:16 by dchrysov         ###   ########.fr       */
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
			return (perror(*ptr), NULL);
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
	return (free_array(path), exit_with_error(name, 127), NULL);
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

/**
 * @brief Handles all execution, for both externals and builtins commands
 */
void	handle_command(t_data *inp)
{
	int	sfd[2];

	sfd[0] = dup(STDIN_FILENO);
	sfd[1] = dup(STDOUT_FILENO);
	if (inp->pipe.num_cmd != 1)
		handle_pipes(inp);
	else
	{
		parse_redir(inp);
		if (!errno)
		{
			if (search_builtins(*inp))
				inp->ret_val = exec_builtin(inp->command, inp->env);
			else
				inp->ret_val = fork_command(inp);
		}
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
