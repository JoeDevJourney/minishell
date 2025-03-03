/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/03 19:36:05 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

/**
 * @brief Searches the $PATH directories for the exec
 */
static char	*path_to_exec(t_data inp)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**path;
	int				i;

	path = ft_split(get_env_val(inp.env, "PATH"), ':');
	if (!path)
		return (perror("$PATH"), NULL);
	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		if (!dir)
			return (free_array(path), perror(path[i]), NULL);
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strncmp(*inp.command, entry->d_name, ft_strlen(*inp.command))
				&& entry->d_name[ft_strlen(*inp.command)] == '\0')
				return (closedir(dir), path[i]);
			entry = readdir(dir);
		}
		closedir (dir);
	}
	return (path[i]);
}

/**
 * @brief Executes an external command
 */
void	exec_external(t_data inp)
{
	char	*dir;
	char	*full_path;

	dir = ft_strjoin(path_to_exec(inp), "/");
	full_path = ft_strjoin(dir, *inp.command);
	free(*inp.command);
	*inp.command = ft_strdup(full_path);
	free(full_path);
	free(dir);
	execve(*inp.command, inp.command, inp.env);
}

/**
 * @brief Creates the child process for a single command
 */
static int	fork_command(t_data inp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_external(inp);
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
 * @brief Checks the input if it's a valid command or a valid directory
 */
void	handle_command(t_data *inp)
{
	struct stat	info;

	if (!ft_strchr(*inp->command, '/'))
	{
		if (search_builtins(*inp))
			inp->ret_val = exec_builtin(inp);
		else if (path_to_exec(*inp))
			inp->ret_val = fork_command(*inp);
		else
			return (printf("%s: command not found\n", *inp->command),
				(void)(inp->ret_val = 127));
	}
	else
	{
		if (stat(*inp->command, &info) == -1)
		{
			printf("%s: No such file or directory\n", *inp->command);
			inp->ret_val = 126;
		}
		else
			inp->ret_val = fork_command(*inp);
	}
	free_redir(inp);
	free_commands(inp);
	init_redir(inp);
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
		// print_data(*inp);
		if (process_fds(inp))					//  && quotes()
			handle_command(inp);
		else
			inp->ret_val = 1;
	}
	dup2(sfd[0], STDIN_FILENO);
	dup2(sfd[1], STDOUT_FILENO);
	close(sfd[0]);
	close(sfd[1]);
}
