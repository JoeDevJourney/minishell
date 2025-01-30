/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/30 18:09:11 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_data	inp;

	printf("Welcome\n");
	// inp.str = readline("Enter command: ");
	inp.str = "cat src/pipes/infile || pwd";
	while (strncmp(inp.str, "exit", 4))
	{
		add_history(inp.str);
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
				if (inp.pipe.num_cmd != 1)
					inp.pipe.ret_code = exec_pipes(inp.pipe.num_cmd, inp.pipe.cmd);			//successful pipe returns 0??
				else
					inp.pipe.ret_code = externals(inp.pipe.cmd);
				inp.or.ret_code = inp.pipe.ret_code;
				if (!inp.or.ret_code)
					break ;
				inp.or.cmd++;
			}
			if (inp.or.ret_code)
				break ;
			inp.and.cmd++;
		}
		inp.str = readline("Enter command: ");
		while (!*inp.str)
			inp.str = readline("Enter command: ");
	}
	// safe_free()
	return (0);
}

// ls -l | grep "\.c" > output.txt
// cat < in.txt | grep "pattern" > med.txt || cat < in1.txt | grep "pattern" > med.txt && sort med.txt >> output.txt
// ls > temp.txt | cat < temp.txt
// ls -1 | cat -n
// echo This is a text | cat -n
// cat src/pipes/infile | cat -e