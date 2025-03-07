/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:19:43 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/07 18:42:28 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

static inline void	update_shell_lvl(t_data *inp)
{
	int		lvl;
	char	*shlvl_val;
	char	*lvl_str;

	lvl = 1;
	shlvl_val = get_env_val(*inp, "SHLVL");
	if (shlvl_val)
		lvl = ft_atoi(shlvl_val) + 1;
	lvl_str = ft_itoa(lvl);
	if (lvl_str)
	{
		update_env_var(&inp->env, "SHLVL", lvl_str);
		free(lvl_str);
	}
}

static inline void	restart_minishell(t_data *inp)
{
	pid_t				pid;
	int					status;
	char				*args[1];
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	sa_new.sa_handler = SIG_IGN;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	pid = fork();
	if (pid == 0)
	{
		sa_new.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa_new, NULL);
		setup_signals();
		args[0] = "./minishell";
		execve(args[0], args, inp->env);
		exit_with_error("execve failed", 1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		sigaction(SIGINT, &sa_old, NULL);
	}
}

/**
 * @brief Prompt
 */
static inline char	*read_input(t_data inp)
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
	setup_signals();
	init_data(&inp, env);
	printf("Welcome\n");
	// while (1)
	// {
	// 	if (g_signal == 1)
	// 	{
	// 		g_signal = 0;
	// 		continue ;
	// 	}
	// 	inp.cmd = read_input(inp);
	// 	if (!inp.cmd)
	// 		break ;
	// 	if ((!ft_strncmp(inp.cmd, "./minishell", 11) && ft_strlen(inp.cmd) == 11)
	// 		|| (!ft_strncmp(inp.cmd, "./minishell ", 12) && ft_strlen(inp.cmd) == 12))
	// 		restart_minishell(&inp);
	// 	else if (valid_oper(&inp.cmd, "&&") && valid_oper(&inp.cmd, "||"))
	// 		parse_n_tokenize(&inp);
	// 	free(inp.cmd);
	// }
	inp.cmd = ft_strdup("cat < Makefile > out");
	if (valid_oper(&inp.cmd, "&&") && valid_oper(&inp.cmd, "||"))
		parse_n_tokenize(&inp);
	free_array(inp.env);
	free(inp.home_dir);
	free(inp.cmd);
	return (0);
}
