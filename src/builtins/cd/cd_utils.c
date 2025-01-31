/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/31 17:06:16 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	ft_write_error(const char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

char	*get_home_dir(void)
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
		home = "/";
	return (home);
}

char	*get_oldpwd_dir(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (oldpwd == NULL)
		ft_write_error("cd: OLDPWD not set\n");
	return (oldpwd);
}

char	*get_target_dir(char **args)
{
	char	*dir;

	if (args[1] != NULL && args[2] != NULL)
		return (NULL);
	if (args[1] == NULL)
		dir = get_home_dir();
	else if (ft_strcmp(args[1], "-") == 0)
	{
		dir = get_oldpwd_dir();
		if (dir == NULL)
			return (NULL);
		printf("s\n", dir);
	}
	else
	{
		dir = args[1];
		if (dir[0] == '\0')
			return (NULL);
	}
	return (dir);
}
