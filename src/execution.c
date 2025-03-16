/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/16 18:28:55 by jbrandt          ###   ########.fr       */
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
	char			*res;
	int				i;

	path = ft_split(get_env_val(inp, "PATH"), ':');
	res = NULL;
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
				if (!res)
					res = ft_strdup(path[i]);
			entry = readdir(dir);
		}
		closedir (dir);
	}
	return (free_array(path), res);
}

/**
 * @brief Executes an external command
 */
void	exec_external(t_data inp)
{
	char	*dir;
	char	*path;
	char	*full_path;


	path = path_to_exec(inp);
	dir = ft_strjoin(path, "/");
	free(path);
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
static int	fork_command(t_data *inp)
{
	pid_t	pid;
	int		status;
	bool	is_heredoc;

	is_heredoc = false;
	pid = fork();
	g_signal = 1;
	setup_signals(g_signal);
	if (pid == 0)
	{
		if (is_heredoc)
		{
			setup_hdoc_signal();
			hdoc_prompt(inp, 0);
		}
		else
			exec_external(*inp);
	}
	if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
		g_signal = 0;
		setup_signals(g_signal);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (130);
	}
	return (perror("Fork failed"), -1);
}

/**
 * @brief Checks the input if it's a valid command or a valid directory
 */
static int	exec_command(t_data *inp)
{
	struct stat	info;
	char		*p;

	parse_input(inp);
	if (process_fds(inp) && *inp->tok)
	{
		if (!ft_strchr(*inp->tok, '/')
			|| ((!ft_strncmp(*inp->tok, "./minishell", 11))
				&& (ft_strlen(*inp->tok) == 11 || ft_strlen(*inp->tok) == 12)))
		{
			p = path_to_exec(*inp);
			if (search_builtins(*inp))
				return (free(p), exec_builtin(inp));
			else if (p)
				return (free(p), fork_command(inp));
			return (free(p), printf("%s: command not found\n", *inp->tok), 127);
		}
		if (stat(*inp->tok, &info) == 0 && S_ISDIR(info.st_mode))
			return (printf("%s: is a directory\n", *inp->tok), 126);
		return (printf("%s: No such file or directory\n", *inp->tok), 127);
	}
	return (1);
}

/**
 * @brief Handles all execution, for both externals and builtin commands
 */
void	parse_n_exec(t_data *inp)
{
	int		sfd[2];
	char	*hdoc;

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
	hdoc = ft_strjoin(inp->home_dir, "/obj/heredoc");
	if (!access(hdoc, F_OK))
		unlink(hdoc);
	free(hdoc);
}
