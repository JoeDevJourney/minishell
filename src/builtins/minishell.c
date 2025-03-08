/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:47:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/08 13:28:50 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	restart_minishell(t_data *inp)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	sa_new.sa_handler = SIG_IGN;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	pid = fork();
	if (pid == 0)
	{
		sa_new.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa_new, NULL);
		setup_signals(g_signal);
		main(0, NULL, inp->env);
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, &status, 0) == -1)
		exit_with_error("Child process failed", EXIT_FAILURE);
	g_signal = 0;
	setup_signals(g_signal);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
