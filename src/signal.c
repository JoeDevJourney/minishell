/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:39:16 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/31 21:17:01 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Signal handler for child processes.
 * 
 * Handles SIGINT and SIGQUIT signals in child processes.
 * @param sig Signal number.
 */
void	child_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		signal(SIGQUIT, SIG_IGN);
	}
}

/**
 * @brief Signal handler for parent process.
 * 
 * Handles SIGINT signal in parent process, resets readline.
 * @param sig Signal number.
 */
void	parent_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @brief Sets up signal handlers for parent or child process.
 * 
 * @param is_child If true, sets child handlers; otherwise parent handlers.
 */
void	setup_signals(bool is_child)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (is_child)
	{
		sa.sa_handler = child_signal;
		sigaction(SIGQUIT, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = parent_signal;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

/**
 * @brief Handles the exit status of a process, including signal termination.
 * 
 * @param status Status value returned by wait().
 * @return int Normalized exit code.
 */
int	handle_signal_status(int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
			return (1);
		return (WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
			return (131);
	}
	return (1);
}
