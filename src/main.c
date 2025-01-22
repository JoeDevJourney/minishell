/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/22 17:55:12 by dchrysov         ###   ########.fr       */
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


int main(void)
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
			// if (token[0] == *list)
			// else
			if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
				printf("%s\n", getenv("PWD"));
			else if (!ft_strncmp(cmd, "ls", ft_strlen(cmd)))
			{
				char *argv[] = {"/bin/ls", "-l", "-a", NULL};
				char *envp[] = {NULL};
				execute_command("/bin/ls", argv, envp);
			}
			// else if (cmd == " ") -> do nothing
			cmd = readline("Enter command: ");
			// else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
			// else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
			// else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
			// else if (!ft_strncmp(cmd, "$?", ft_strlen(cmd)))
		}
	}
	return (5);
}
