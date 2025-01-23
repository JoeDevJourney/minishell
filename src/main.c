/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/23 17:56:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	execute_command(char *cmd, char *argv[], char *envp[])
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

	printf("Welcome\n");
	cmd = readline("Enter command: ");

	//operators = [&&, |, <, <<, >, >>]
	// search cmd for operators

	// if pipe

	// else search for redir operators

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

// ls -l | grep "\.c" > output.txt
// cat input.txt | grep "pattern" > med.txt && sort med.txt >> output.txt