/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/28 19:11:25 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	child(char *cmd, int *p_fd)
{
	char	*tok[2];

	close(p_fd[0]);
	dup2(p_fd[1], 1);
	tok[0] = cmd;
	tok[1] = NULL;
	externals(tok);
	close(p_fd[1]);
	exit(0);
}

static void	parent(char *cmd, int *p_fd)
{
	char	*tok[2];

	close(p_fd[1]);
	dup2(p_fd[0], 0);
	tok[0] = cmd;
	tok[1] = NULL;
	externals(tok);
	close(p_fd[0]);
	exit(0);
}

void	exec_pipe(char **argv)
{
	pid_t	pid1;
	pid_t	pid2;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
	{
		ft_putstr_fd("pipex: environment not found\n", 2);
		exit(1);
	}
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		child(argv[0], p_fd);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
		parent(argv[1], p_fd);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	int		p_fd[2];

// 	(void)argc;
// 	create_child_process(++argv, p_fd);
// 	close(p_fd[0]);
// 	close(p_fd[1]);
// 	return (0);
// }
