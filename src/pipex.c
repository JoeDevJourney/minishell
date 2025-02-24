/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/24 17:32:28 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_pipes(t_redir_op *oper)
{
	int	i;

	oper->fd = safe_malloc(oper->num_cmd * sizeof(int *));
	i = -1;
	while (++i < oper->num_cmd - 1)
		oper->fd[i] = safe_malloc(2 * sizeof(int));
	i = -1;
	while (++i < oper->num_cmd - 1)
	{
		if (pipe(oper->fd[i]) == -1)
		{
			while (--i >= 0)
			{
				close(oper->fd[i][0]);
				close(oper->fd[i][1]);
				free(oper->fd[i]);
			}
			free(oper->fd);
			exit_with_error("Pipe creation failed", EXIT_FAILURE);
		}
	}
	oper->fd[i] = NULL;
}

/**
 * @brief Redirection of the pipes' fds
 */
static void	process_pipe_fds(t_data *inp, int *old_fd, int *new_fd)
{
	if (*new_fd == STDOUT_FILENO)
	{
		dup2(old_fd[1], *new_fd);
		close (old_fd[1]);
	}
	else if (*new_fd == STDIN_FILENO)
	{
		dup2(old_fd[0], *new_fd);
		close (old_fd[1]);
	}
	else
	{
		close(new_fd[0]);
		dup2(old_fd[0], STDIN_FILENO);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
	close(old_fd[0]);
	if (!search_builtins(*inp))
		exec_external(*inp);
	else
		exec_builtin(inp);
	exit(0);
}

/**
 * @brief Creates the child process for executing the command and makes
 * the parent wait for it to finish, before returning its value
 */
static int	fork_pipe(pid_t pid, t_data *inp, int *old_fd, int *new_fd)
{
	int	status;

	process_fds(inp);
	pid = fork();
	if (pid == 0)
		process_pipe_fds(inp, old_fd, new_fd);
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
		free_redir(inp);
		free_commands(inp);
		init_redir(inp);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	else
		perror("Fork failed");
	return (free_commands(inp), 0);
}

/**
 * @brief Executes pipe(s) when given the (char **) cmd(s).
 */
void	handle_pipes(t_data *inp)
{
	t_data	inp_cpy;
	pid_t	*pid;
	int		fd;
	int		i;

	pid = (pid_t *)safe_malloc(inp->pipe.num_cmd * sizeof(pid_t));
	init_pipes(&inp->pipe);
	inp_cpy = *inp;
	i = 0;
	fd = STDOUT_FILENO;
	fork_pipe(pid[i], &inp_cpy, inp->pipe.fd[i], &fd);
	while (++i < inp_cpy.pipe.num_cmd - 1)
	{
		close(inp->pipe.fd[i - 1][1]);
		inp_cpy.pipe.cmd++;
		fork_pipe(pid[i], &inp_cpy, inp->pipe.fd[i - 1], inp->pipe.fd[i]);
		close(inp->pipe.fd[i - 1][0]);
	}
	close(inp->pipe.fd[i - 1][1]);
	inp_cpy.pipe.cmd++;
	fd = STDIN_FILENO;
	inp->ret_val = fork_pipe(pid[i], &inp_cpy, inp->pipe.fd[i - 1], &fd);
	close(inp->pipe.fd[i - 1][0]);
	free(pid);
	free_array_fd(inp->pipe.fd);
}
