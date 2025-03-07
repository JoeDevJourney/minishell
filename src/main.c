/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/07 11:46:37 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (free_flag & 1)
		free(s1);
	if (free_flag & 2)
		free(s2);
	return (result);
}

/**
 * @brief Prompt
 */
static char	*read_input(char **env)
{
	char	*str;
	char	*prompt;
	char	*user;
	char	*pwd;

	user = get_env_val(env, "USER");
	pwd = get_env_val(env, "PWD");
	prompt = ft_strjoin3(GRN, user, " @ ");
	prompt = ft_strjoin_free(prompt, ft_strrchr(pwd, '/') + 1, 1);
	prompt = ft_strjoin_free(prompt, RST " % ", 1);
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
	inp->env = NULL;
	dupl_env(&inp->env, env);
	inp->home_dir = ft_strdup(getenv("PWD"));
	inp->and.cmd = NULL;
	inp->and.num_cmd = 0;
	inp->or.cmd = NULL;
	inp->or.num_cmd = 0;
	inp->pipe.cmd = NULL;
	inp->pipe.num_cmd = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;

	(void)argc;
	(void)argv;
	setup_signals();
	init_data(&inp, env);
	update_shell_lvl(&inp);
	printf("Welcome\n");
	while (1)
	{
		if (g_signal == 1)
		{
			g_signal = 0;
			continue ;
		}
		inp.input = read_input(inp.env);
		if (!inp.input)
			break ;
		if (ft_strcmp(inp.input, "./minishell") == 0 ||
			ft_strcmp(inp.input, "./minishell ") == 0)
		{
			restart_minishell(&inp);
			free(inp.input);
			continue ;
		}
		if (valid_oper(&inp.input, "&&") && valid_oper(&inp.input, "||"))
			parse_logic(&inp);
		free(inp.input);
	}
	free(inp.home_dir);
	free(inp.input);
	free_array(inp.env);
	return (0);
}

