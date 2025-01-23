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

// void	execute_command(char *cmd, char *argv[], char *envp[])
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		execve(cmd, argv, envp);
// 		perror("execve");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid > 0)
// 		wait(NULL);
// 	else
// 		perror("fork");
// }

int	main(void)
{
	t_data	inp;

	printf("Welcome\n");
	inp.str = readline("Enter command: ");
	inp.and.cmd = ft_split2(inp.str, "&&");
	inp.and.num_cmd = count_substr(inp.str, "&&");
	while (*inp.and.cmd)
	{
		inp.or.cmd = ft_split2(*inp.and.cmd, "||");
		inp.or.num_cmd = count_substr(*inp.and.cmd, "||");
		while (*inp.or.cmd)
		{
			inp.pipe.cmd = ft_split2(*inp.or.cmd, "|");
			inp.pipe.num_cmd = count_substr(*inp.or.cmd, "|");
			while (*inp.pipe.cmd)
			{
				// cmd = redir_oper(*pipe_cmd);
				// pipe()
			}								//successful pipe returns 0??
			if (!inp.pipe.ret_code)
			{
				// inp.or.ret_code = (!= 0)
				break ;
			}
			pause();
		}
		if (inp.or.ret_code)
			break ;
		inp.and.cmd++;
	}
	// while (strncmp(cmd, "exit", ft_strlen(cmd)))
	// {
	// 	if (cmd && *cmd)
	// 	{
	// 		add_history(cmd);
	// 		externals(&cmd);
	// 		cmd = readline("Enter command: ");
	// 	}
	// }
	return (0);
}

// ls -l | grep "\.c" > output.txt
// cat < in.txt | grep "pattern" > med.txt || cat < in1.txt | grep "pattern" > med.txt && sort med.txt >> output.txt
// ls > temp.txt | cat < temp.txt