/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/31 15:51:25 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	process(char *cmd, int *old_fd, int *new_fd)
{
	char	*tok[2];

	tok[0] = cmd;
	tok[1] = NULL;
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
	execute_command(tok);
	exit(0);
}

static int	**init_pipes(int n)
{
	int	i;
	int	**fd;

	fd = (int **)safe_malloc((n - 1) * sizeof(int *));
	i = -1;
	while (++i < n - 1)
		fd[i] = (int *)safe_malloc((2 * sizeof(int)));
	i = -1;
	while (++i < n - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd("pipex: pipe creation failed\n", 2);
			while (i > 0)
				free(fd[--i]);
			free(fd);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

static void	fork_pr(pid_t pid, char *cmd, int *old_fd, int *new_fd)
{
	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (pid == 0)
		process(cmd, old_fd, new_fd);
}

static void	wait_n_free(int n, pid_t *pid, int **pfd)
{
	int	i;
	int	status;

	i = -1;
	while (++i < n)
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			perror("Waiting child process failed");
			exit(EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < n - 1)
		free(pfd[i]);
	free(pid);
	free(pfd);
}

/**
 * @brief Executes pipes when given the cmds stored as an array of str.
 * 
 * @param num Number of commands
 * @param cmd Commands broken down in an array of str
 */
int	exec_pipes(int num, char **cmd)
{
	pid_t	*pid;
	int		**p_fd;
	int		ptr_fd;
	int		i;

	pid = (pid_t *)safe_malloc(num * sizeof(pid_t));
	p_fd = init_pipes(num);
	i = 0;
	ptr_fd = STDOUT_FILENO;
	fork_pr(pid[i], cmd[i], p_fd[i], &ptr_fd);
	while (++i < num - 1)
	{
		close(p_fd[i - 1][1]);
		fork_pr(pid[i], cmd[i], p_fd[i - 1], p_fd[i]);
		close(p_fd[i - 1][i - 1]);
	}
	close(p_fd[i - 1][1]);
	ptr_fd = STDIN_FILENO;
	fork_pr(pid[i], cmd[i], p_fd[i - 1], &ptr_fd);
	close(p_fd[i - 1][0]);
	wait_n_free(num, pid, p_fd);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	exec_pipes(--argc, ++argv);
// 	return (0);
// }
// ./pipex "ls -1" "cat -n"
// ./pipex "echo This is a text" "cat -n"
// ./pipex "ls -a" "cat -n" "cat -e"