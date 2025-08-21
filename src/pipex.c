/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/31 19:29:12 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Waits for all child processes to finish and frees pipe fds.
 * 
 * @param inp Pointer to the main data structure.
 * @return int The exit status after handling signals.
 */
static int	wait_n_free(t_data *inp)
{
	int	status;
	int	i;

	i = -1;
	while (++i < inp->pipe.num_cmd)
		if (wait(&status) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
	free_array_fd(inp->pipe.fd);
	setup_signals(false);
	return (handle_signal_status(status));
}

/**
 * @brief Initializes the pipe file descriptors for all commands.
 * 
 * @param oper Pointer to the redirection operator structure.
 */
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
 * @brief Handles redirection of file descriptors for a pipe segment.
 * 
 * @param inp Pointer to the main data structure.
 * @param old_fd File descriptors from the previous pipe.
 * @param new_fd File descriptors for the current pipe.
 */
static void	process_pipe_fds(t_data *inp, int *old_fd, int *new_fd)
{
	char	**env;

	env = list_to_array(inp->env);
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
	inp->ret_val = exec_command(inp, true, env);
	free_array(&env, count_array_size(env));
}

/**
 * @brief Forks a child process to execute a command in the pipeline.
 * 
 * @param inp Pointer to the main data structure.
 * @param j Index of the command in the pipeline.
 * @param old_fd File descriptors from the previous pipe.
 * @param new_fd File descriptors for the current pipe.
 * @return int PID of the forked child process.
 */
static int	fork_pipe(t_data *inp, int j, int *old_fd, int *new_fd)
{
	int	pid;

	pid = fork();
	setup_signals(true);
	if (pid == 0)
	{
		inp->pipe.cmd += j;
		if (!parse_input(inp) || !process_fds(inp) || !*inp->tok)
		{
			inp->pipe.cmd -= j;
			free_struct(inp, true);
			exit(1);
		}
		process_pipe_fds(inp, old_fd, new_fd);
		inp->pipe.cmd -= j;
		free_struct(inp, true);
		exit(inp->ret_val);
	}
	return (pid);
}

/**
 * @brief Executes a series of piped commands.
 * 
 * @param inp Pointer to the main data structure.
 * @return int The exit status of the pipeline execution.
 */
int	exec_pipes(t_data *inp)
{
	int		i;

	init_pipes(&inp->pipe);
	i = 0;
	fork_pipe(inp, i, inp->pipe.fd[i + 1], &inp->pipe.fd[0][1]);
	while (++i < inp->pipe.num_cmd)
	{
		close(inp->pipe.fd[i][1]);
		if (i != inp->pipe.num_cmd - 1)
			fork_pipe(inp, i, inp->pipe.fd[i], inp->pipe.fd[i + 1]);
		else
			fork_pipe(inp, i, inp->pipe.fd[i], &inp->pipe.fd[0][0]);
		close(inp->pipe.fd[i][0]);
	}
	return (wait_n_free(inp));
}
