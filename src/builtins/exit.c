/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:31:49 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 18:05:13 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @returns exit_code
 */
int	exec_exit(t_data *inp, char **env)
{
	int	exit_code;

	exit_code = 0;
	if (inp->tok[1] && inp->tok[2])
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	if (inp->tok[1] && !is_numeric(inp->tok[1]))
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", inp->tok[1]);
		exit_code = 255;
	}
	else if (inp->tok[1])
	{
		printf("exit\n");
		exit_code = ft_atoi(inp->tok[1]) % 256;
	}
	exit_free(inp);
	free_array(&env, count_array_size(env));
	exit(exit_code);
}
