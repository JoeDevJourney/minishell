/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:19:43 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 19:11:56 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	update_shell_lvl(t_data *inp)
{
	int		lvl;
	char	*shlvl_val;
	char	*lvl_str;

	lvl = 1;
	shlvl_val = get_env_val(*inp, "SHLVL");
	if (shlvl_val)
	{
		lvl = ft_atoi(shlvl_val) + 1;
		free(shlvl_val);
	}
	lvl_str = ft_itoa(lvl);
	update_env_var(&inp->env, "SHLVL", lvl_str);
	free(lvl_str);
}

static void	init_data(t_data *inp, char **env, int argc, char **argv)
{
	char	*home;

	(void)argc;
	(void)argv;
	inp->env = NULL;
	dupl_env(&inp->env, env);
	inp->pid = getpid();
	update_shell_lvl(inp);
	home = get_env_val(*inp, "PWD");
	if (home)
		inp->home_dir = home;
	else
		inp->home_dir = ft_strdup("/");
	inp->input = NULL;
	inp->pipe.cmd = NULL;
	inp->pipe.num_cmd = 0;
	inp->cmd = NULL;
	inp->tok = NULL;
	inp->ret_val = 0;
	init_redir(inp);
}

/**
 * @brief Generates the prompt
 * 
 * @note Handles empty commands, or commands with only spaces
 */
static bool	read_input(t_data *inp)
{
	char	*prompt;
	char	*trim;

	prompt = build_prompt(inp);
	while (true)
	{
		inp->input = readline(prompt);
		if (!inp->input)
			return (free(prompt), false);
		trim = ft_strtrim(inp->input, " ");
		free(inp->input);
		inp->input = trim;
		if (*inp->input)
			break ;
		free(inp->input);
	}
	return (add_history(inp->input), free(prompt), true);
}

/**
 * @brief Checks if there's a hanging command near an operator
 * 
 * @note It doesn't work for commands with mixed operators.
 */
static bool	valid_pipe(t_data *inp)
{
	char	*trim;
	int		i;

	i = -1;
	while (inp->pipe.cmd[++i])
	{
		if (inp->pipe.cmd[i])
		{
			trim = ft_strtrim(inp->pipe.cmd[i], " ");
			free(inp->pipe.cmd[i]);
			inp->pipe.cmd[i] = trim;
		}
		if (inp->pipe.cmd[i][0] == '\0')
		{
			free_array(&inp->pipe.cmd, inp->pipe.num_cmd);
			printf("bash: syntax error near unexpected token `|'\n");
			return (free(inp->input), inp->ret_val = 258, false);
		}
	}
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;
	char	*hdoc;

	init_data(&inp, env, argc, argv);
	setup_signals(false);
	printf("Welcome\n");
	while (1)
	{
		if (!read_input(&inp))
			break ;
		inp.pipe.cmd = ft_split2(inp.input, "|");
		inp.pipe.num_cmd = count_delim(inp.input, "|");
		if (valid_pipe(&inp))
			parse_n_exec(&inp);
		hdoc = ft_strjoin(inp.home_dir, "/obj/heredoc");
		if (!access(hdoc, F_OK))
			unlink(hdoc);
		free(hdoc);
	}
	return (free(inp.home_dir), free_env_list(inp.env), 0);
}

// if (!isatty(fileno(stdin)))
// {
// 	char *line;
// 	line = get_next_line(fileno(stdin));
// 	inp.input = ft_strtrim(line, "\n");
// 	free(line);
// }
// else