/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:48:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/21 19:22:41 by dchrysov         ###   ########.fr       */
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
	while (path && path[++i])
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
	if (path)
		free_array(path);
	return (res);
}

/**
 * @brief Creates the child process for a single command
 */
static int	fork_command(t_data *inp)
{
	pid_t	pid;
	int		status;
	char	**env;

	pid = fork();
	setup_signals(true);
	env = list_to_array(inp->env);
	if (pid == 0)
		execve(*inp->tok, inp->tok, env);
	if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
		free_array(env);
		setup_signals(false);
		return (handle_signal_status(status));
	}
	return (perror("Fork failed"), -1);
}

static void	set_full_path(t_data *inp)
{
	char	*dir;
	char	*path;
	char	*full_path;

	path = path_to_exec(*inp);
	dir = ft_strjoin_free(path, "/");
	full_path = ft_strjoin_free(dir, *inp->tok);
	free(*inp->tok);
	*inp->tok = ft_strdup(full_path);
	free(full_path);
}

/**
 * @brief Checks the input if it's a valid command or a valid directory
 */
int	exec_command(t_data *inp, bool pipe_flag, char **env)
{
	struct stat	info;

	if (search_builtins(*inp))
		return (exec_builtin(inp));
	if (stat(*inp->tok, &info) == -1 && S_ISDIR(info.st_mode))
		return (printf("%s: No such file or directory\n", *inp->tok), 127);
	if (access(*inp->tok, F_OK) == -1)
	{
		set_full_path(inp);
		if (access(*inp->tok, F_OK) == -1)
			return (printf("%s: command not found\n", *inp->tok + 1), 127);
	}
	if (access(*inp->tok, X_OK) == -1)
		return (perror(*inp->tok), errno);
	if (!access(*inp->tok, F_OK) && pipe_flag)
		return (execve(*inp->tok, inp->tok, env));
	if (!access(*inp->tok, F_OK) && !pipe_flag)
		return (fork_command(inp));
	return (printf("%s: is a directory\n", *inp->tok), 126);
}

/**
 * @brief Handles all execution, for both externals and builtin commands
 */
void	parse_n_exec(t_data *inp)
{
	int		sfd[2];
	char	**env;

	sfd[0] = dup(STDIN_FILENO);
	sfd[1] = dup(STDOUT_FILENO);
	env = list_to_array(inp->env);
	if (inp->pipe.num_cmd != 1)
		inp->ret_val = exec_pipes(inp);
	else
	{
		parse_input(inp);
		if (process_fds(inp) && inp->tok && *inp->tok)
			inp->ret_val = exec_command(inp, false, env);
		else
			inp->ret_val = 1;
	}
	dup2(sfd[0], STDIN_FILENO);
	dup2(sfd[1], STDOUT_FILENO);
	close(sfd[0]);
	close(sfd[1]);
	free_array(env);
	return (free_redir(inp), free_commands(inp), init_redir(inp));
}
