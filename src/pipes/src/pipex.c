/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/29 18:38:31 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	exec_process(char *cmd, int input_fd, int output_fd)
{
	char	*tok[2];

	tok[0] = cmd;
	tok[1] = NULL;
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
	printf("executing comand: %s\n", tok[0]);
	return (externals(tok));
}

int	exec_pipe(char *cmds[], int num_cmds)
{
	int		*pipe_fd;
	pid_t	pid;
	int		i;
	int		res;

	res = 0;
	pipe_fd = (int *)malloc(2 * (num_cmds - 1) * sizeof(int));
	if (!pipe_fd)
	{
		perror("malloc error");
		return (0);
	}
	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipe_fd + i * 2) == -1)
		{
			perror("pipe error");
			free(pipe_fd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < num_cmds)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			free(pipe_fd);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (i != 0)
			{
				dup2(pipe_fd[(i - 1) * 2], STDIN_FILENO);
				close(pipe_fd[(i - 1) * 2]);
			}
			if (i != num_cmds - 1)
			{
				dup2(pipe_fd[i * 2 + 1], STDOUT_FILENO);
				close(pipe_fd[i * 2 + 1]);
			}
			for (int j = 0; j < 2 * (num_cmds - 1); j++) {
				if (j != (i - 1) * 2 && j != i * 2 + 1)
				close(pipe_fd[j]);
			}
			printf("Child %d executing command: %s\n", i, cmds[i]);
			res = exec_process(cmds[i], STDIN_FILENO, STDOUT_FILENO);
		}
		i++;
	}
	for (int j = 0; j < 2 * (num_cmds - 1); j++) {
		close(pipe_fd[j]);
	}
	for (int j = 0; j < num_cmds; j++) {
		waitpid(-1, NULL, 0);
		printf("Parent waiting for child %d\n", j);
	}
	return (res);
}

int	main(int argc, char **argv)
{
	// exec_pipe(--argc, ++argv);
    exec_pipe(++argv, --argc);
	return (0);
}
// ./pipex "ls -1" "cat -n"
// ./pipex "echo This is a text" "cat -n"
// ./pipex "ls -a" "cat -n" "cat -e"