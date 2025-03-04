/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/04 20:55:52 by dchrysov         ###   ########.fr       */
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
	// int	sfd[2];

	// sfd[0] = dup(STDIN_FILENO);
	// sfd[1] = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		if (inp->input)
			free(inp->input);
		inp->input = ft_strdup(*inp->pipe.cmd);
		if (!process_fds(inp))
			exec_exit(0);
		process_pipe_fds(inp, old_fd, new_fd);
	}
	// dup2(sfd[0], STDIN_FILENO);
	// dup2(sfd[1], STDOUT_FILENO);
	// close(sfd[0]);
	// close(sfd[1]);
	return (pid);
}

/**
 * @brief Executes pipe(s) when given the (char **) cmd(s).
 */
int	handle_pipes(t_data *inp)
{
	t_data	ptr;
	pid_t	*pid;
	int		i;

	pid = (pid_t *)safe_malloc(inp->pipe.num_cmd * sizeof(pid_t));
	init_pipes(&inp->pipe);
	ptr = *inp;
	i = 0;
	pid[i] = fork_pipe(&ptr, ptr.pipe.fd[i + 1], &ptr.pipe.fd[0][1]);
	while (++i < ptr.pipe.num_cmd)
	{
		close(ptr.pipe.fd[i][1]);
		ptr.pipe.cmd++;
		if (i != ptr.pipe.num_cmd - 1)
			pid[i] = fork_pipe(&ptr, ptr.pipe.fd[i], ptr.pipe.fd[i + 1]);
		else
			pid[i] = fork_pipe(&ptr, ptr.pipe.fd[i], &ptr.pipe.fd[0][0]);
		close(ptr.pipe.fd[i][0]);
	}
	return (wait_n_free(&ptr, pid));
}
