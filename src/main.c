/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:19:43 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/07 12:02:59 by dchrysov         ###   ########.fr       */
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
static char	*read_input(t_data inp)
{
	char	*str;
	char	*prompt;
	char	*user;
	char	*pwd;

	user = get_env_val(inp, "USER");
	pwd = get_env_val(inp, "PWD");
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
	inp->pid = getpid();
	inp->env = NULL;
	dupl_env(&inp->env, env);
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
	printf("Welcome\n");
	while (1)
	{
		inp.cmd = read_input(inp);
		if (valid_oper(&inp.cmd, "&&") && valid_oper(&inp.cmd, "||"))
			parse_n_tokenize(&inp);
	}
	free(inp.home_dir);
	free(inp.cmd);
	free_array(inp.env);
	return (0);
}
