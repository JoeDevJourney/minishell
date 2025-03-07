/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:39:16 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/07 20:43:46 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	child_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		g_signal = 0;
	}
}

static void	parent_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	setup_signals(int is_child)
{
	struct sigaction	sa;

	rl_catch_signals = 0;

	if (is_child)
		sa.sa_handler = child_signal;
	else
		sa.sa_handler = parent_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
