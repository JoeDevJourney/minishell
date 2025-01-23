/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/23 15:42:20 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void execute_command(char *cmd, char *argv[], char *envp[])
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");
}


int	main(void)
{
	char	*cmd;
	// char **list = external commands 

	printf("Welcome\n");
	cmd = readline("Enter command: ");
	// tokenize

	while (strncmp(cmd, "exit", ft_strlen(cmd)))
	{
		if (cmd && *cmd)
		{
			add_history(cmd);
			externals(&cmd);
			cmd = readline("Enter command: ");
		}
	}
	return (5);
}
