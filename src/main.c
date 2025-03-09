/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:19:43 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 16:09:31 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

/**
 * @brief Prompt
 */
static char	*read_input(t_data inp)
{
	char	*str;
	char	*prompt;
	char	*user;
	char	*pwd;

	user = get_env_val(inp, "USER");
	pwd = get_env_val(inp, "PWD");
	prompt = ft_strjoin3(GRN, user, " @ ");
	prompt = ft_strjoin_free(prompt, ft_strrchr(pwd, '/') + 1);
	prompt = ft_strjoin_free(prompt, RST " % ");
	str = readline(prompt);
	while (str && !*str)
	{
		free(str);
		str = readline(prompt);
	}
	if (str)
		add_history(str);
	free(prompt);
	return (str);
}

static void	init_data(t_data *inp, char **env)
{
	inp->pid = getpid();
	inp->env = NULL;
	dupl_env(&inp->env, env);
	update_shell_lvl(inp);
	inp->home_dir = ft_strdup(getenv("PWD"));
	inp->and.cmd = NULL;
	inp->and.num_cmd = 0;
	inp->or.cmd = NULL;
	inp->or.num_cmd = 0;
	inp->pipe.cmd = NULL;
	inp->pipe.num_cmd = 0;
	inp->ret_val = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;

	(void)argc;
	(void)argv;
	init_data(&inp, env);
	setup_signals(g_signal);
	printf("Welcome: SHLVL %s\n", get_env_val(inp, "SHLVL"));
	while (1)
	{
		inp.cmd = read_input(inp);
		// if (!ft_strncmp(inp.cmd, " ", 1) && ft_strlen(inp.cmd) == 1)
		// 	continue ;
		// check for spaces
		if (!inp.cmd)
		{
			printf("exit SHLVL %s\n", get_env_val(inp, "SHLVL"));
			break ;
		}
		if ((valid_oper(&inp.cmd, "&&")) && valid_oper(&inp.cmd, "||")
			&& valid_oper(&inp.cmd, "|"))
			parse_n_tokenize(&inp);
		else
			inp.ret_val = 258;
		free(inp.cmd);
	}
	// inp.cmd = ft_strdup("cat < Makefile > out");
	// if (valid_oper(&inp.cmd, "&&") && valid_oper(&inp.cmd, "||"))
	// 	parse_n_tokenize(&inp);
	free_array(inp.env);
	free(inp.home_dir);
	free(inp.cmd);
	return (0);
}
