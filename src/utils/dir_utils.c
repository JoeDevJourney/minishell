/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/09 21:58:57 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_home_dir(t_data inp)
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

static char	*get_oldpwd_dir(t_data inp)
{
	char	*oldpwd;

	oldpwd = get_env_val(inp, "OLDPWD");
	if (!oldpwd)
		printf("bash: cd: OLDPWD not set\n");
	return (oldpwd);
}

static char	*process_argument(t_data inp)
{
	char	*trimmed;
	char	*res;

	if (!ft_strncmp(inp.tok[1], "-", 1) && ft_strlen(inp.tok[1]) == 1)
	{
		if (!get_oldpwd_dir(inp))
			return (NULL);
		printf("%s\n", get_oldpwd_dir(inp));
		return (ft_strdup(get_oldpwd_dir(inp)));
	}
	if (inp.tok[1][0] == '~')
	{
		if (!get_home_dir(inp))
			return (NULL);
		return (ft_strjoin3(get_home_dir(inp), "/", inp.tok[1] + 1));
	}
	if (inp.tok[1][0] == '\0')
		return (NULL);
	if (inp.tok[1][0] == '/')
		return (ft_strdup(inp.tok[1]));
	trimmed = ft_strtrim(inp.tok[1], "/");
	res = ft_strjoin3(get_env_val(inp, ("PWD")), "/", trimmed);
	return (free(trimmed), res);
}

char	*get_target_dir(t_data inp)
{
	char	*home;

	if (!inp.tok[1])
	{
		home = ft_strdup(get_home_dir(inp));
		if (!home)
			return (NULL);
		return (home);
	}
	return (process_argument(inp));
}
