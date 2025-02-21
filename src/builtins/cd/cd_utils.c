/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/21 16:07:24 by jbrandt          ###   ########.fr       */
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


char	*get_home_dir(void)
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
	{
		perror("cd: HOME not set\n");
		return (NULL);
	}
	return (home);
}

char	*get_oldpwd_dir(void)
{
	char	*oldpwd;

	oldpwd = getenv("OLDPWD");
	if (oldpwd == NULL)
		perror("cd: OLDPWD not set\n");
	return (oldpwd);
}
