/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/29 16:19:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	mid_process(char *cmd, int *old_fd, int *new_fd)
{
	char	*tok[2];

	tok[0] = cmd;
	tok[1] = NULL;
	close(old_fd[1]);
	close(new_fd[0]);
	dup2(old_fd[0], STDIN_FILENO);
	dup2(new_fd[1], STDOUT_FILENO);
	close(old_fd[1]);
	close(new_fd[0]);
	externals(tok);
	exit(0);
}

static void	edge_process(char *cmd, int *old_fd, int new_fd)
{
	char	*tok[2];

	tok[0] = cmd;
	tok[1] = NULL;
	if (new_fd == STDOUT_FILENO)
	{
		close (old_fd[0]);
		dup2(old_fd[1], new_fd);
		close(old_fd[1]);
	}
	else if (new_fd == STDIN_FILENO)
	{
		close (old_fd[1]);
		dup2(old_fd[0], new_fd);
		close(old_fd[0]);
	}
	externals(tok);
	exit(0);
}

int	exec_pipe(int num, char **cmd)
{
	pid_t	*pid;											// #number of processes
	int		**p_fd;											// #number of pipes
	int		i;

	pid = (pid_t *)malloc(num * sizeof(pid_t));
	if (!pid)
		return (0);
	if (num == 2)
		p_fd = (int **)malloc(sizeof(int *));
	else
		p_fd = (int **)malloc((num - 1) * sizeof(int *));
	if (!p_fd)
		return (0);
	i = 0;
	while (i < num)
	{
		p_fd[i] = (int *)malloc((2 * sizeof(int)));
		if (!p_fd[i])
			return (0);
		i++;
	}
	i = 0;
	if (pipe(p_fd[i]) == -1)
	{
		ft_putstr_fd("pipex: pipe creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	pid[i] = fork();
	if (pid[i] == -1)
		exit (EXIT_FAILURE);
	if (pid[i] == 0)
		edge_process(cmd[i], p_fd[i], STDOUT_FILENO);
	while (++i < num - 1)
	{
		if (pipe(p_fd[i]) == -1)
		{
			ft_putstr_fd("pipex: environment not found\n", 2);
			exit(EXIT_FAILURE);
		}
		pid[i] = fork();
		if (pid[i] == -1)
			exit(EXIT_FAILURE);
		if (pid[i] == 0)
			mid_process(cmd[i], p_fd[i - 1], p_fd[i]);
	}
	pid[i] = fork();
	if (pid[i] == -1)
		exit (EXIT_FAILURE);
	if (pid[i] == 0)
		edge_process(cmd[i], p_fd[i - 1], STDIN_FILENO);
	i = 0;
	while (i < num - 1)
	{
		close(p_fd[i][0]);
		close(p_fd[i][1]);
		i++;
	}
	i = 0;
	while (i < num)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	i = 0;
	while (i < num - 1)
	{
		free(p_fd[i]);
		i++;
	}
	free(pid);
	free(p_fd);
	return (0);
}

int	main(int argc, char **argv)
{
	exec_pipe(--argc, ++argv);
	return (0);
}
// ./pipex "ls -1" "cat -n"
// ./pipex "echo This is a text" "cat -n"
// ./pipex "ls -a" "cat -n" "cat -e"