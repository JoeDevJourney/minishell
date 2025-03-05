/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/05 20:45:03 by dchrysov         ###   ########.fr       */
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
			if (!ft_strncmp(*inp.tok, entry->d_name, ft_strlen(*inp.tok))
				&& entry->d_name[ft_strlen(*inp.tok)] == '\0')
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
	full_path = ft_strjoin(dir, *inp.tok);
	free(*inp.tok);
	*inp.tok = ft_strdup(full_path);
	free(full_path);
	free(dir);
	execve(*inp.tok, inp.tok, inp.env);
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
static int	exec_command(t_data *inp)
{
	struct stat	info;

	parse_command(inp);
	if (process_fds(inp))
	{
		if (!ft_strchr(*inp->tok, '/'))
		{
			// print_data(*inp);
			if (search_builtins(*inp))
				return (exec_builtin(inp));
			else if (path_to_exec(*inp))						//Needs freeing
				return (fork_command(*inp));
			return (printf("%s: command not found\n", *inp->tok), 127);
		}
		else
		{
			if (stat(*inp->tok, &info) == 0 && S_ISDIR(info.st_mode))
				return (printf("%s: is a directory\n", *inp->tok), 126);
			return (printf("%s: No such file or directory\n", *inp->tok),
				127);
		}
	}
	else
		return (1);
}

/**
 * @brief Handles all execution, for both externals and builtin commands
 */
void	parse_n_exec(t_data *inp)
{
	int	sfd[2];

	sfd[0] = dup(STDIN_FILENO);
	sfd[1] = dup(STDOUT_FILENO);
	if (inp->pipe.num_cmd != 1)
		inp->ret_val = exec_pipes(inp);
	else
		inp->ret_val = exec_command(inp);
	free_redir(inp);
	free_commands(inp);
	init_redir(inp);
	dup2(sfd[0], STDIN_FILENO);
	dup2(sfd[1], STDOUT_FILENO);
	close(sfd[0]);
	close(sfd[1]);
}
