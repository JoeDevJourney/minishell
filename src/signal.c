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
	// if (sig == SIGQUIT)
		//do nothing
}

static void	child_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("here\n");
		exec_exit((char *[]){ft_itoa(131), NULL});
		// rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
		signal(SIGQUIT, SIG_DFL);
}

int	signal_handlers()
{
	struct sigaction	sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
	if (is_child == 1)
	{
		printf("here\n");
		sa.sa_handler = child_signal;
	}
	else
    	sa.sa_handler = parent_signal;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
	return (0);
}
