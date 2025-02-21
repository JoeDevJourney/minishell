/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:10:49 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/20 18:54:49 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_argument(char *arg)
{
	char	*dir;
	char	*home;

	if (ft_strcmp(arg, "-") == 0)
	{
		dir = get_oldpwd_dir();
		if (dir)
		{
			printf("%s\n", dir);
			dir = ft_strdup(dir);
		}
		return (dir);
	}
	if (arg[0] == '~')
	{
		home = get_home_dir();
		if (!home)
			return (NULL);
		dir = ft_strjoin(home, arg + 1);
		return (dir);
	}
	if (arg[0] == '\0')
		return (NULL);
	return (ft_strdup(arg));
}

char	*get_target_dir(char **args)
{
	char	*home;

	if (args[1] && args[2])
		return (NULL);
	if (!args[1])
	{
		home = get_home_dir();
		if (home)
			return (ft_strdup(home));
		return (NULL);
	}
	return (process_argument(args[1]));
}
