/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:39:16 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/09 21:30:19 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_signal = 0;
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
	}
}

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
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
		sa.sa_handler = parent_signal;
		sigaction(SIGINT, &sa, NULL);
	}
}
