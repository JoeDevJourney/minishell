/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:47:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/21 17:36:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Restarts the minishell in a child process.
 * 
 * @param inp Pointer to main data structure.
 * @return int Exit status.
 */
int	restart_minishell(t_data *inp)
{
	pid_t				pid;
	int					status;
	char				**env;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	sa_new.sa_handler = SIG_IGN;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	pid = fork();
	env = list_to_array(inp->env);
	if (pid == 0)
	{
		sa_new.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa_new, NULL);
		setup_signals(false);
		main(0, NULL, env);
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, &status, 0) == -1)
		exit_with_error("Child process failed", EXIT_FAILURE);
	setup_signals(false);
	free_array(&env, count_array_size(env));
	return (handle_signal_status(status));
}
