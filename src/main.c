/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:19:43 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 12:09:30 by dchrysov         ###   ########.fr       */
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
	char	*user;
	char	*pwd;
	char	*trim;
	char	*temp;

	temp = get_env_val(*inp, "USER");
	if (temp)
		user = temp;
	else
		user = ft_strdup("");
	prompt = ft_strjoin3(GRN, user, " @ ");
	free(user);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/");
	prompt = ft_strjoin_free(&prompt, ft_strrchr(pwd, '/') + 1);
	prompt = ft_strjoin_free(&prompt, RST " % ");
	while (true)
	{
		inp->input = readline(prompt);
		if (!inp->input)
			return (free(pwd), free(prompt), false);
		trim = ft_strtrim(inp->input, " ");
		free(inp->input);
		inp->input = trim;
		if (*inp->input)
			break ;
		free(inp->input);
	}
	return (add_history(inp->input), free(pwd), free(prompt), true);
}

/**
 * @brief Checks if there's a hanging command near an operator
 * 
 * @note It doesn't work for commands with mixed operators.
 */
static bool	valid_op(t_data *inp, char *del)
{
	char	**arr;
	int		num_del;

	if (ft_strlen(del) == 1)
		num_del = count_oper(inp->input, *del, false);
	else
		num_del = count_oper(inp->input, *del, true);
	arr = ft_split2(inp->input, del);
	int i = -1;
	while (arr[++i])
		printf("'%s'\n", arr[i]);
	if ((int)count_array_size(arr) != num_del + 1 || arr[0][0] == '\0')
	{
		inp->ret_val = 258;
		printf("bash: syntax error near unexpected token `%s'\n", del);
		free(inp->input);
		free_array(&arr, count_array_size(arr));
		return (false);
	}
	return (free_array(&arr, count_array_size(arr)), true);
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
		if (valid_op(&inp, "|") && valid_op(&inp, ">>") && valid_op(&inp, ">")
			&& valid_op(&inp, "<<") && valid_op(&inp, "<"))
		{
			exit(0);
			inp.pipe.cmd = ft_split2(inp.input, "|");
			inp.pipe.num_cmd = count_delim(inp.input, "|");
			parse_n_exec(&inp);
		}
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