/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:48:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/30 13:40:42 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Searches the $PATH directories for the exec
 */
static void	path_to_exec(t_data inp, char **path)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**arr;
	int				i;
	char			*temp;

	temp = get_env_val(inp, "PATH");
	arr = ft_split(temp, ':');
	i = -1;
	while (arr && arr[++i])
	{
		dir = opendir(arr[i]);
		if (!dir)
			return (free_array(&arr, count_array_size(arr)), perror(arr[i]));
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strncmp(*inp.tok, entry->d_name, ft_strlen(*inp.tok))
				&& entry->d_name[ft_strlen(*inp.tok)] == '\0')
				if (!*path)
					*path = ft_strdup(arr[i]);
			entry = readdir(dir);
		}
		closedir (dir);
	}
	free(temp);
	if (arr)
		free_array(&arr, count_array_size(arr));
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
		free_array(&env, count_array_size(env));
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

	path = NULL;
	path_to_exec(*inp, &path);
	if (!path)
		path = ft_strdup("");
	dir = ft_strjoin(path, "/");
	free(path);
	full_path = ft_strjoin(dir, *inp->tok);
	free(dir);
	free(*inp->tok);
	*inp->tok = full_path;
}

/**
 * @brief Checks the input if it's a valid command or a valid directory
 */
int	exec_command(t_data *inp, bool pipe_flag, char **env)
{
	struct stat	info;

	if (search_builtins(*inp))
		return (exec_builtin(inp, env));
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
	if (inp->pipe.num_cmd != 1)
		inp->ret_val = exec_pipes(inp);
	else if (parse_input(inp) && process_fds(inp) && inp->tok && *inp->tok)
	{
		env = list_to_array(inp->env);
		inp->ret_val = exec_command(inp, false, env);
		free_array(&env, count_array_size(env));
	}
	dup2(sfd[0], STDIN_FILENO);
	dup2(sfd[1], STDOUT_FILENO);
	close(sfd[0]);
	close(sfd[1]);
	return (free_redir(inp), free_commands(inp), init_redir(inp));
}
