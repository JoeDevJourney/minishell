/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 12:38:44 by dchrysov         ###   ########.fr       */
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

/**
 * @brief Extracts the env variable from the env list.
 */
char	*get_env_val(t_data inp, char *name)
{
	size_t	name_len;
	int		i;

	name_len = ft_strlen(name);
	i = -1;
	if (!ft_strncmp(name, "\?", 1) && name_len == 1)
		return (ft_itoa(inp.ret_val));
	while (inp.env[++i])
		if (!ft_strncmp(inp.env[i], name, name_len)
			&& inp.env[i][name_len] == '=')
			return (&inp.env[i][name_len + 1]);
	return (NULL);
}

char	*get_home_dir(t_data inp)
{
	char	*home;

	home = get_env_val(inp, "HOME");
	if (home == NULL)
	{
		perror("cd: HOME not set\n");
		return (NULL);
	}
	return (home);
}

char	*get_oldpwd_dir(t_data inp)
{
	char	*oldpwd;

	oldpwd = get_env_val(inp, "OLDPWD");
	if (!oldpwd)
		perror("cd: OLDPWD not set\n");
	return (oldpwd);
}
