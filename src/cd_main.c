/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/03 14:30:49 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;

char	*create_env_entry(const char *name, const char *value)
{
	char	*new_entry;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_entry = malloc(len);
	if (!new_entry)
	{
		ft_write_error("cd: malloc failed\n");
		return (NULL);
	}
	ft_strcpy(new_entry, name);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	return (new_entry);
}

int	replace_env_var(const char *name, char *new_entry)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)) == 0 && environ[i][ft_strlen(name)] == '=')
		{
			free(environ[i]);
			environ[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (-1);
}

int	update_env_var(const char *name, const char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (1);
	if (replace_env_var(name, new_entry) == 0)
		return (0);
	if (add_env_var(new_entry) != 0)
		return (1);
	return (0);
}

int	ft_cd(char **args)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = getenv("PWD");
	dir = get_target_dir(args);
	if (!dir)
		return (1);
	if (chdir(dir) != 0)
		return (1);
	if (update_pwd_vars(oldpwd) != 0)
		return (1);
	return (0);
}
