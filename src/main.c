/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:19:43 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/20 15:35:45 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

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
	if (!user)
		user = "";
	pwd = getcwd(NULL, 0);
	prompt = ft_strjoin3(GRN, user, " @ ");
	prompt = ft_strjoin_free(prompt, ft_strrchr(pwd, '/') + 1);
	prompt = ft_strjoin_free(prompt, RST " % ");
	free(pwd);
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

static bool	trim_user_input(t_data *inp)
{
	char	*trimmed;

	if (!inp->cmd)
		return (printf("exit SHLVL %s\n", get_env_val(*inp, "SHLVL")), false);
	trimmed = ft_strtrim(inp->cmd, " ");
	free(inp->cmd);
	inp->cmd = trimmed;
	return (true);
}

/**
 * @brief Checks if there's a hanging command near an operator
 * 
 * @note It doesn't work for commands with mixed operators.
 */
static bool	valid_oper(char **cmd, char *del)
{
	int		i;
	int		size;
	char	*input;
	char	**arr;
	char	*trimmed;

	arr = ft_split2(*cmd, del);
	size = count_array_size(arr);
	i = -1;
	while (++i < size)
	{
		trimmed = ft_strtrim(arr[i], " ");
		free(arr[i]);
		arr[i] = trimmed;
		if (i < size - 1 && arr[i][0] == '\0')
			return (free_array(arr),
				printf("bash: syntax error near unexpected token `%s'\n", del), false);
		if (i == size - 1 && arr[i][0] == '\0')
		{
			input = readline("");
			*cmd = ft_strjoin_free(*cmd, input);
			free(input);
		}
	}
	return (free_array(arr), true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;

	(void)argc;
	(void)argv;
	init_data(&inp, env);
	setup_signals(false);
	printf("Welcome: SHLVL %s\n", get_env_val(inp, "SHLVL"));
	while (1)
	{
		inp.cmd = read_input(inp);
		if (!trim_user_input(&inp))
			break ;
		if (!ft_strncmp(inp.cmd, " ", 1))
			continue ;
		if ((valid_oper(&inp.cmd, "&&")) && valid_oper(&inp.cmd, "||")
			&& valid_oper(&inp.cmd, "|"))
			parse_n_tokenize(&inp);
		else
			inp.ret_val = 258;
		free(inp.cmd);
	}
	free(inp.home_dir);
	free_env_list(inp.env);
	free(inp.cmd);
	return (0);
}

// if (isatty(fileno(stdin)))
// inp.cmd = read_input(inp);
// else
// {
// char *line;
// line = get_next_line(fileno(stdin));
// inp.cmd = ft_strtrim(line, "\n");
// free(line);
// }