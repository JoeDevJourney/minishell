/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/03 18:19:25 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *read_input()
{
	char	*str;

	printf("%s%s@%s %s%% ", GRN, getenv("USER"), relative_wd(getenv("PWD")), RST);
	str = readline("");
	while (!*str)
	{
		printf("%s%s@%s %s%% ", GRN, getenv("USER"), relative_wd(getenv("PWD")), RST);
		str = readline("");
	}
	add_history(str);
	return(str);
}

int	main(void)
{
	t_data	inp;

	printf("Welcome\n");
	inp.str = read_input();
	while (strncmp(inp.str, "exit", 4) != 0)
	{
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
				if (is_builtin(inp.pipe.cmd[0]))
					inp.pipe.ret_val = execute_builtin(inp.pipe.cmd);
				else
					inp.pipe.ret_val = exec_pipes(inp.pipe.num_cmd, inp.pipe.cmd);
				safe_free(inp.pipe.cmd);
				inp.or.ret_val = inp.pipe.ret_val;
				if (!inp.or.ret_val)
					break ;
				inp.or.cmd++;
			}
			safe_free(inp.or.cmd);
			inp.and.ret_val = inp.or.ret_val;
			if (inp.and.ret_val)
				break ;
			inp.and.cmd++;
		}
		safe_free(inp.and.cmd);
		safe_free(inp.str);
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