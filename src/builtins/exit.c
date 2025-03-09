/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:31:49 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 14:04:42 by jbrandt          ###   ########.fr       */
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
int	exec_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1] && args[2])
	{
		printf("exit\n");
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	if (args[1] && !is_numeric(args[1]))
	{
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit_code = 255;
	}
	else if (args[1])
	{
		printf("exit\n");
		exit_code = ft_atoi(args[1]) % 256;
	}
	exit(exit_code);
}
