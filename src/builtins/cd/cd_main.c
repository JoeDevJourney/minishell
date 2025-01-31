/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/31 18:09:02 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern char	**environ;

char	*create_env_entry(const char *name, const char *value)
{
	char	*new_entry;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_entry = malloc(len);
	if (new_entry == NULL)
	{
		ft_write_error("cd: malloc failed\n");
		return (NULL);
	}
	ft_strcpy(new_entry, name);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	return (new_entry);
}

int	replace_env_var(char *name, char *new_entry)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)) == 0 && \
			environ[i][ft_strlen(name)] == '=')
		{
			free(environ[i]);
			environ = new_entry;
			return (0);
		}
		i++;
	}
	ft_write_error("cd: environment variable not found\n");
	free(new_entry);
	return (1);
}

int	update_env_var(const char *name, const char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(name, value);
	if (new_entry == NULL)
		return (1);
	if (replace_env_var(name, new_entry) != 0)
		return (1);
	return (0);
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
		write(STDOUT_FILENO, dir, strlen(dir));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		dir = args[1];
		if (dir[0] == '\0')
			return (NULL);
	}
	return (dir);
}

int	ft_cd(char **args)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = getenv("PWD");
	dir = get_target_dir(args);
	if (dir == NULL)
		return (1);
	if (chdir(dir) != 0)
		return (1);
	if (update_pwd_vars(oldpwd) != 0)
		return (1);
	return (0);
}
