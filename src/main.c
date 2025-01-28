/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/28 20:27:44 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_data	inp;

	printf("Welcome\n");
	// inp.str = readline("Enter command: ");
	inp.str = "ls -l | cat -n | cat -e";
	inp.and.cmd = ft_split2(inp.str, "&&");
	if (!inp.and.cmd)
	{
		printf("Error: Failed to parse command\n");
		exit (1);
	}
	inp.and.num_cmd = count_substr(inp.str, "&&");
	while (*inp.and.cmd)
	{
		inp.or.cmd = ft_split2(*inp.and.cmd, "||");
		inp.or.num_cmd = count_substr(*inp.and.cmd, "||");
		while (*inp.or.cmd)
		{
			inp.pipe.cmd = ft_split2(*inp.or.cmd, "|");
			inp.pipe.num_cmd = count_substr(*inp.or.cmd, "|");
			printf("%d\n", inp.pipe.num_cmd);
			exec_pipe(inp.pipe.cmd);							//successful pipe returns 0??
			// if (!inp.pipe.ret_code)
			// {
			// 	inp.or.ret_code = ? (!= 0)
			// 	break ;
			// }
			inp.or.cmd++;
		}
		// if (inp.or.ret_code)
		// 	break ;
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