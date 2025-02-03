/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:10:49 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/03 16:12:47 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"cd", "exit", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(char **args)
{
	char	*builtins[3];
	int		i;

	builtins[0] = "cd";
	builtins[1] = "exit";
	builtins[2] = NULL;
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(args[0], builtins[i]) == 0)
			break ;
		i++;
	}
	if (ft_strcmp(builtins[i], "cd") == 0)
		return (ft_cd(args));
	else if (ft_strcmp(builtins[i], "exit") == 0)
		return (ft_exit(args));
	return (127);
}

int	ft_exit(char **args)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	exit (status);
}
