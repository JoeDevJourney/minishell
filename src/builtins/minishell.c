/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:47:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/20 19:58:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	restart_minishell(t_data *inp)
{
	pid_t				pid;
	int					status;
	char				**env;

	pid = fork();
	env = list_to_array(inp->env);
	if (pid == 0)
	{
		main(0, NULL, env);
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, &status, 0) == -1)
		exit_with_error("Child process failed", EXIT_FAILURE);
	free_array(env);
	return (0);
}
