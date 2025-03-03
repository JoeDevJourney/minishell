/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/03 13:14:08 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	wait_n_free(t_data *inp, int *pid)
{
	int	status;
	int	i;

	i = -1;
	while (++i < inp->pipe.num_cmd)
		if (waitpid(pid[i], &status, 0) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
	free_redir(inp);
	free_commands(inp);
	init_redir(inp);
	free(pid);
	free_array_fd(inp->pipe.fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

static void	init_pipes(t_redir_op *oper)
{
	int	i;

	oper->fd = safe_malloc((oper->num_cmd + 1) * sizeof(int *));
	i = 0;
	oper->fd[i] = safe_malloc(2 * sizeof(int));
	oper->fd[i][0] = STDIN_FILENO;
	oper->fd[i][1] = STDOUT_FILENO;
	while (++i < oper->num_cmd)
	{
		oper->fd[i] = safe_malloc(2 * sizeof(int));
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
}

/**
 * @brief Creates the child process for executing the command and makes
 * the parent wait for it to finish, before returning its value
 */
static int	fork_pipe(t_data *inp, int *old_fd, int *new_fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!process_fds(inp))
			exec_exit(0);
		process_pipe_fds(inp, old_fd, new_fd);
	}
	return (pid);
}

/**
 * @brief Executes pipe(s) when given the (char **) cmd(s).
 */
int	handle_pipes(t_data *inp)
{
	t_data	inp_cpy;
	pid_t	*pid;
	int		i;

	pid = (pid_t *)safe_malloc(inp->pipe.num_cmd * sizeof(pid_t));
	init_pipes(&inp->pipe);
	inp_cpy = *inp;
	i = 0;
	pid[i] = fork_pipe(&inp_cpy, inp->pipe.fd[i + 1], &inp->pipe.fd[0][1]);
	while (++i < inp_cpy.pipe.num_cmd)
	{
		close(inp->pipe.fd[i][1]);
		inp_cpy.pipe.cmd++;
		if (i != inp_cpy.pipe.num_cmd - 1)
			pid[i] = fork_pipe(&inp_cpy, inp->pipe.fd[i], inp->pipe.fd[i + 1]);
		else
			pid[i] = fork_pipe(&inp_cpy, inp->pipe.fd[i], &inp->pipe.fd[0][0]);
		close(inp->pipe.fd[i][0]);
	}
	return (wait_n_free(inp, pid));
}
