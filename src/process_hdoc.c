/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:07:25 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 16:13:39 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Signal handler for heredoc input (handles SIGINT).
 * 
 * @param sig Signal number.
 */
static void	hdoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		ioctl(0, TIOCSTI, "\4");
	}
}

/**
 * @brief Sets up custom signal handling for heredoc input.
 */
static void	setup_hdoc_signal(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = hdoc_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Reads user input for heredoc, handling signals and EOF.
 * 
 * @param inp Pointer to main data structure.
 * @param input Pointer to store the input string.
 * @return true if input was read, false otherwise.
 */
static bool	hdoc_read_input(t_data *inp, char **input)
{
	setup_hdoc_signal();
	*input = readline("> ");
	if (!*input)
	{
		if (g_signal == 0)
			printf("> ");
		else if (g_signal == 1)
		{
			inp->ret_val = 1;
			g_signal = 0;
		}
		return (false);
	}
	return (true);
}

/**
 * @brief Prompts the user for heredoc input until delimiter is reached.
 * 
 * @param inp Pointer to main data structure.
 * @param i Index of the heredoc command.
 */
static void	hdoc_prompt(t_data *inp, int i)
{
	char	*input;
	char	*del;

	if (ft_strchr(inp->hdoc_op.cmd[i], '"'))
		del = ft_strtrim(inp->hdoc_op.cmd[i], "\"");
	else if (ft_strchr(inp->hdoc_op.cmd[i], '\''))
		del = ft_strtrim(inp->hdoc_op.cmd[i], "'");
	else
		del = ft_strdup(inp->hdoc_op.cmd[i]);
	input = NULL;
	while (1)
	{
		if (!hdoc_read_input(inp, &input) || (*input != '\0'
				&& !ft_strncmp(input, del, ft_strlen(input))
				&& ft_strlen(input) == ft_strlen(del)))
		{
			free(input);
			break ;
		}
		write_to_fd(&input, inp, i);
		free(input);
	}
	setup_signals(false);
	free(del);
}

/**
 * @brief Processes heredoc operation for the current command.
 * 
 * @note Need to add the expansion functionality in the user input
 * @param inp Pointer to main data structure.
 * @return true if heredoc was processed successfully, false otherwise.
 */
bool	hdoc_oper(t_data *inp)
{
	static size_t	i;
	char			*hdoc;

	if (!setup_heredoc_fd(inp, &hdoc, i))
		return (false);
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
