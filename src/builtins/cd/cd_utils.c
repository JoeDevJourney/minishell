/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/05 16:57:52 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	{
		ft_write_error("cd: HOME not set\n");
		return (NULL);
	}
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
