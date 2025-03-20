/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:07:25 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/20 15:22:15 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	hdoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		ioctl(0, TIOCSTI, "\4");
	}
}

void	setup_hdoc_signal(void)
{
	struct sigaction	sa;

	g_signal = 0;
	rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = hdoc_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Checks for quotes in the delimeter
 * 
 * @returns the delimeter trimmed of quotes
 * 
 * @note return 1 if there were quotes in the first place, 0 otherwise
 */
// static bool	trim_delimeter(char **del)
// {
// 	char	*trimmed;
// 	bool	res;

// 	check_open_quotes(del);
// 	res = false;
// 	if (ft_strchr(*del, '\''))
// 	{
// 		trimmed = ft_strtrim(*del, "'");
// 		free(*del);
// 		*del = trimmed;
// 		res = true;
// 	}
// 	if (ft_strchr(*del, '"'))
// 	{
// 		trimmed = ft_strtrim(*del, "\"");
// 		free(*del);
// 		*del = trimmed;
// 		res = true;
// 	}
// 	return (res);
// }

static void	write_to_fd(char **input, t_data *inp, int i)
{
	char	*trimmed;

	check_open_quotes(&inp->hdoc_op.cmd[i]);
	while (ft_strchr(inp->hdoc_op.cmd[i], '\''))
	{
		trimmed = ft_strtrim(inp->hdoc_op.cmd[i], "'");
		free(inp->hdoc_op.cmd[i]);
		inp->hdoc_op.cmd[i] = ft_strtrim(trimmed, "'");
		free(trimmed);
	}
	while (ft_strchr(inp->hdoc_op.cmd[i], '"'))
	{
		trimmed = ft_strtrim(inp->hdoc_op.cmd[i], "\"");
		free(inp->hdoc_op.cmd[i]);
		inp->hdoc_op.cmd[i] = ft_strtrim(trimmed, "\"");
		free(trimmed);
	}
	if (ft_strchr(inp->hdoc_op.cmd[i], '"')
		|| ft_strchr(inp->hdoc_op.cmd[i], '\''))
		ft_putendl_fd(*input, *inp->hdoc_op.fd[1]);
	else
	{
		expansion(input, *inp);
		ft_putendl_fd(*input, *inp->hdoc_op.fd[1]);
	}
}

void	hdoc_prompt(t_data *inp, int i)
{
	char	*input;

	setup_hdoc_signal();
	input = NULL;
	while (1)
	{
		if (!hdoc_read_input(inp, &input))
			break ;
		if (*input != '\0'
			&& !ft_strncmp(input, inp->hdoc_op.cmd[i], ft_strlen(input))
			&& ft_strlen(input) == ft_strlen(inp->hdoc_op.cmd[i]))
		{
			free(input);
			break ;
		}
		write_to_fd(&input, inp, i);
		free(input);
	}
	setup_signals(false);
	g_signal = 0;
}

/**
 * @note Need to add the expansion functionality in the user input
 */
bool	hdoc_oper(t_data *inp)
{
	static size_t	i;
	char			*hdoc;

	hdoc = ft_strjoin(inp->home_dir, "/obj/heredoc");
	inp->hdoc_op.fd = safe_malloc(3 * sizeof(int *));
	inp->hdoc_op.fd[0] = safe_malloc(sizeof(int));
	*inp->hdoc_op.fd[0] = STDIN_FILENO;
	inp->hdoc_op.fd[1] = safe_malloc(sizeof(int));
	*inp->hdoc_op.fd[1] = open(hdoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*inp->hdoc_op.fd[1] == -1)
		return (perror(inp->hdoc_op.cmd[i]), false);
	inp->hdoc_op.fd[2] = NULL;
	setup_hdoc_signal();
	hdoc_prompt(inp, i);
	if (inp->ret_val == 1)
		return (close(*inp->hdoc_op.fd[1]), free_array_fd(inp->hdoc_op.fd),
			free(hdoc), false);
	close(*inp->hdoc_op.fd[1]);
	*inp->hdoc_op.fd[1] = open(hdoc, O_RDONLY);
	if (!inp->hdoc_op.cmd[++i])
		dup2(*inp->hdoc_op.fd[1], *inp->hdoc_op.fd[0]);
	if (i == count_array_size(inp->hdoc_op.cmd))
		i = 0;
	return (close(*inp->hdoc_op.fd[1]), free_array_fd(inp->hdoc_op.fd),
		free(hdoc), true);
}
