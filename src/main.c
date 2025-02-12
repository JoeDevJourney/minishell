/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/12 14:38:09 by dchrysov         ###   ########.fr       */
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

static void	parse_command(t_data *inp)
{
	char	**and_cmd;
	char	**or_cmd;

	inp->and.cmd = ft_split2(inp->str, "&&");
	inp->and.num_cmd = count_substr(inp->str, "&&");
	and_cmd = inp->and.cmd;
	while (*and_cmd)
	{
		inp->or.cmd = ft_split2(*inp->and.cmd, "||");
		inp->or.num_cmd = count_substr(*inp->and.cmd, "||");
		or_cmd = inp->or.cmd;
		while (*or_cmd)
		{
			inp->pipe.cmd = ft_split2(*inp->or.cmd, "|");
			inp->pipe.num_cmd = count_substr(*inp->or.cmd, "|");
			if (inp->pipe.num_cmd != 1)
				inp->ret_val = handle_pipes(inp);
			else
				inp->ret_val = handle_command(inp);
			if (!inp->ret_val)
				break ;
			or_cmd++;
		}
		if (inp->ret_val)
			break ;
		and_cmd++;
	}
	(void)free_input(inp);
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;

	(void)argc;
	(void)argv;
	inp.env = env;
	inp.home_dir = ft_strdup(getenv("PWD"));
	printf("Welcome\n");
	while (1)
	{
		inp.str = read_input();
		if (!ft_strncmp(inp.str, "exit", ft_strlen(inp.str)))
			break ;
		parse_command(&inp);
	}
	// free(inp.home_dir);
	// free(inp.str);
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
