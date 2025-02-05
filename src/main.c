/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/05 16:57:08 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*read_input(void)
{
	char	*str;
	char	*prompt;
	char	*temp;

	temp = ft_strjoin(GRN, getenv("USER"));
	prompt = ft_strdup(temp);
	free(temp);
	temp = ft_strjoin(prompt, "@");
	free(prompt);
	prompt = ft_strjoin(temp, rwd(getenv("PWD")));
	free(temp);
	temp = ft_strjoin(prompt, RST);
	free(prompt);
	prompt = ft_strjoin(temp, " % ");
	str = readline(prompt);
	while (!str)
		str = readline(prompt);
	add_history(str);
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;

	(void)argc;
	(void)argv;
	inp.env = env;
	inp.home_dir = ft_strdup(getenv("PWD"));
	printf("Welcome\n");
	inp.str = read_input();
	while (strncmp(inp.str, "exit", 4))
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
				if (inp.pipe.num_cmd != 1)
					inp.pipe.ret_val = handle_pipes(inp);
				else
					inp.pipe.ret_val = handle_command(inp);
				inp.or.ret_val = inp.pipe.ret_val;
				if (!inp.or.ret_val)
					break ;
				inp.or.cmd++;
			}
			inp.and.ret_val = inp.or.ret_val;
			if (inp.and.ret_val)
				break ;
			inp.and.cmd++;
		}
		inp.str = read_input();
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


// In case duplicating env is needed
// int count = 0;
// while (env[count])
// 	count++;
// inp.env = malloc((count + 1) * sizeof(char *));				// Needs freeing
// if (!inp.env)
// 	return (0);
// for (int i = 0; i < count; i++)
// {
// 	inp.env[i] = ft_strdup(env[i]);
// 	if (!inp.env[i])
// 	{
// 		return (0);
// 		while (i > 0)
// 			free(inp.env[--i]);
// 		free(inp.env);
// 		return (0);
// 	}
// }
