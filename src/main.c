/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:19:43 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/27 19:12:28 by dchrysov         ###   ########.fr       */
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
		lvl = ft_atoi(shlvl_val) + 1;
	lvl_str = ft_itoa(lvl);
	if (lvl_str)
	{
		update_env_var(&inp->env, "SHLVL", lvl_str);
		free(lvl_str);
	}
}

static void	init_data(t_data *inp, char **env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	inp->pid = getpid();
	inp->env = NULL;
	dupl_env(&inp->env, env);
	update_shell_lvl(inp);
	inp->home_dir = ft_strdup(getenv("PWD"));
	inp->pipe.cmd = NULL;
	inp->pipe.num_cmd = 0;
	inp->cmd = NULL;
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
	char	*user;
	char	*pwd;
	char	*trim;

	user = get_env_val(*inp, "USER");
	if (!user)
		user = "";
	prompt = ft_strjoin3(GRN, user, " @ ");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/");
	prompt = ft_strjoin_free(prompt, ft_strrchr(pwd, '/') + 1);
	prompt = ft_strjoin_free(prompt, RST " % ");
	while (true)
	{
		inp->cmd = readline(prompt);
		if (!inp->cmd)
			return (free(pwd), free(prompt), false);
		trim = ft_strtrim(inp->cmd, " ");
		free(inp->cmd);
		inp->cmd = ft_strdup(trim);
		if (*inp->cmd)
			break ;
		free(inp->cmd);
	}
	return (add_history(inp->cmd), free(pwd), free(prompt), free(trim), true);
}

/**
 * @brief Checks if there's a hanging command near an operator
 * 
 * @note It doesn't work for commands with mixed operators.
 */
static bool	valid_oper(t_data *inp, char *del)
{
	int		i;
	int		size;
	char	*input;
	char	**arr;
	char	*trimmed;

	arr = ft_split2(inp->cmd, del);
	size = count_array_size(arr);
	i = -1;
	while (++i < size)
	{
		trimmed = ft_strtrim(arr[i], " ");
		free(arr[i]);
		arr[i] = trimmed;
		if (i < size - 1 && arr[i][0] == '\0')
			return (inp->ret_val = 258, printf("bash: syntax error near"
					" unexpected token `%s'\n", del), false);
		if (i == size - 1 && arr[i][0] == '\0')
		{
			input = readline("");
			inp->cmd = ft_strjoin_free(inp->cmd, input);
			free(input);
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
	printf("Welcome: SHLVL %s\n", get_env_val(inp, "SHLVL"));
	while (1)
	{
		if (!read_input(&inp))
			break ;
		if (valid_oper(&inp, "|"))
		{
			inp.pipe.cmd = ft_split2(inp.cmd, "|");
			inp.pipe.num_cmd = count_delim(inp.cmd, "|");
			parse_n_exec(&inp);
		}
		hdoc = ft_strjoin(inp.home_dir, "/obj/heredoc");
		if (!access(hdoc, F_OK))
			unlink(hdoc);
		if (hdoc)
			free(hdoc);
		free(inp.cmd);
	}
	return (free(inp.home_dir), free_env_list(inp.env), free(inp.cmd), 0);
}
