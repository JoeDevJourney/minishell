/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/19 16:16:52 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Prompt
 */
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
	while (!*str)
		str = readline(prompt);
	add_history(str);
	return (free(temp), free(prompt), str);
}

static void	init_data(t_data *inp, char **env)
{
	int	i;

	inp->env = safe_malloc((count_array_size(env) + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
	{
		inp->env[i] = ft_strdup(env[i]);
		if (!inp->env[i])
		{
			while (i > 0)
				free(inp->env[--i]);
			free(inp->env);
			return ;
		}
	}
	inp->home_dir = ft_strdup(getenv("PWD"));
	inp->and.cmd = NULL;
	inp->and.num_cmd = 0;
	inp->or.cmd = NULL;
	inp->or.num_cmd = 0;
	inp->pipe.cmd = NULL;
	inp->pipe.num_cmd = 0;
}

static void	parse_command(t_data *inp)
{
	int	i;
	int	j;

	inp->and.cmd = ft_split2(inp->input, "&&");
	inp->and.num_cmd = count_substr(inp->input, "&&");
	free(inp->input);
	i = -1;
	while (++i < inp->and.num_cmd)
	{
		inp->or.cmd = ft_split2(inp->and.cmd[i], "||");
		inp->or.num_cmd = count_substr(inp->and.cmd[i], "||");
		j = -1;
		while (++j < inp->or.num_cmd)
		{
			init_redir(inp);
			inp->pipe.cmd = ft_split2(inp->or.cmd[j], "|");
			inp->pipe.num_cmd = count_substr(inp->or.cmd[j], "|");
			handle_command(inp);
			free_array(inp->pipe.cmd);
			if (!inp->ret_val)
				break ;
		}
		free_array(inp->or.cmd);
		if (inp->ret_val)
			break ;
	}
	free_array(inp->and.cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;

	(void)argc;
	(void)argv;
	init_data(&inp, env);
	init_redir(&inp);
	printf("Welcome\n");
	while (1)
	{
		inp.input = read_input();
		if (!ft_strncmp(inp.input, "exit", ft_strlen(inp.input)))
			break ;
		parse_command(&inp);
	}
	free(inp.home_dir);
	free_array(inp.env);
	return (0);
}

// ls -l | grep "\.c" > output.txt
// cat < in.txt | grep "pattern" > med.txt || cat < in1.txt | grep "pattern" > med.txt && sort med.txt >> output.txt
// ls > temp.txt | cat < temp.txt
// ls -1 | cat -n
// echo This is a text | cat -n
// cat src/pipes/infile | cat -e