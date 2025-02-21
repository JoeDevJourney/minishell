/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/21 12:48:32 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_env_entry(const char *name, const char *value)
{
	char	*new_entry;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_entry = malloc(len);
	if (!new_entry)
	{
		perror("cd: malloc failed\n");
		exit (EXIT_FAILURE);
	}
	ft_strcpy(new_entry, name);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	return (new_entry);
}

int	replace_env_var(char **env, const char *name, char *new_entry)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 \
			&& env[i][ft_strlen(name)] == '=')
		{
			env[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (-1);
}

int	update_env_var(char **env, const char *name, const char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (1);
	if (replace_env_var(env, name, new_entry) == 0)
		return (0);
	if (add_env_var(env, new_entry) != 0)
		return (1);
	return (0);
}

int	ft_cd(char **env, char **args)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = getenv("PWD");
	dir = get_target_dir(args);
	if (!dir || chdir(dir) != 0)
		return (perror("cd failed"), 1);
	if (update_pwd_vars(env, oldpwd) != 0)
		return (1);
	return (0);
}
