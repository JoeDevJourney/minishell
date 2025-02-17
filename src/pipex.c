/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/17 20:37:56 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	wait_n_free(int n, pid_t *pid, int **pfd)
{
	int	i;
	int	status;

	i = -1;
	while (++i < n)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			exit_with_error("Pipe child process failed", EXIT_FAILURE);
	}
	i = -1;
	while (++i < n - 1)
		free(pfd[i]);
	free(pid);
	free(pfd);
}

static void	init_pipes(t_redir_op *oper)
{
	int	i;

	oper->fd = safe_malloc(oper->num_cmd * sizeof(int [2]));
	i = -1;
	while (++i < oper->num_cmd)
	{
		if (pipe(oper->fd) == -1)
		{
			while (i > 0)
				free(oper->fd[--i]);
			free(oper->fd);
			exit_with_error("Pipe creation failed", EXIT_FAILURE);
		}
	}
}

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
	exit(0);
}

static int	fork_pipe(pid_t pid, t_data *inp, int *old_fd, int *new_fd)
{
	pid = fork();
	if (pid == 0)
		process_pipe_fds(inp, old_fd, new_fd);
	return (0);
}

/**
 * @brief Executes pipes when given the cmds stored as an array of str.
 * 
 * @param num Number of commands
 * @param cmd Commands broken down in an array of str
 */
int	handle_pipes(t_data *inp)
{
	pid_t	*pid;
	int		std_fd;
	int		i;
	int		res;

	print_data(*inp);
	pid = (pid_t *)safe_malloc(inp->pipe.num_cmd * sizeof(pid_t));
	init_pipes(&inp->pipe);
	i = 0;
	std_fd = STDOUT_FILENO;
	res = fork_pipe(pid[i], inp, p_fd[i], &std_fd);
	while (++i < inp->pipe.num_cmd - 1)
	{
		close(p_fd[i - 1][1]);
		inp->pipe.cmd++;
		res = fork_pipe(pid[i], inp, p_fd[i - 1], p_fd[i]);
		close(p_fd[i - 1][i - 1]);
	}
	close(p_fd[i - 1][1]);
	inp->pipe.cmd++;
	std_fd = STDIN_FILENO;
	res = fork_pipe(pid[i], inp, p_fd[i - 1], &std_fd);
	close(p_fd[i - 1][0]);
	wait_n_free(inp->pipe.num_cmd, pid, p_fd);
	return (res);
}

// int	main(int argc, char **argv)
// {
// 	handle_pipes(--argc, ++argv);
// 	return (0);
// }
// ./pipex "ls -1" "cat -n"
// ./pipex "echo This is a text" "cat -n"
// ./pipex "ls -a" "cat -n" "cat -e"