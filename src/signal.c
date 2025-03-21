/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:39:16 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/20 19:57:07 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	parent_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		rl_replace_line("", 0);
		// printf("a\n\n");
	}
}

static void	child_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		signal(SIGINT, SIG_DFL);
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit\n");
		signal(SIGQUIT, SIG_DFL);
	}
}

int	signal_handlers()
{
	struct sigaction	sa;
	
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (is_child == 1)
		sa.sa_handler = child_signal;
	else
		sa.sa_handler = parent_signal;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
	return (0);
}
