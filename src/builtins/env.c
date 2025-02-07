/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/07 13:26:52 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_env(char **env)
{
	char	**ptr;

	ptr = env;
	while (*ptr)
		printf("%s\n", *ptr++);
}

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	execute_env(env);
// }