/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/24 17:24:05 by dchrysov         ###   ########.fr       */
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

char	*get_env_val(char **env, char *name)
{
	size_t	name_len;
	int		i;

	name_len = ft_strlen(name);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, name_len) && env[i][name_len] == '=')
			return (&env[i][name_len + 1]);
	}
	return (NULL);
}

char	*get_home_dir(char **env)
{
	char	*home;

	home = get_env_val(env, "HOME");
	if (home == NULL)
	{
		perror("cd: HOME not set\n");
		return (NULL);
	}
	return (home);
}

char	*get_oldpwd_dir(char **env)
{
	char	*oldpwd;

	oldpwd = get_env_val(env, "OLDPWD");
	if (!oldpwd)
		perror("cd: OLDPWD not set\n");
	return (oldpwd);
}
