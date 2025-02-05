/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:15:14 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/05 12:35:47 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr != '\0')
		ptr++;
	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dest);
}

int	update_pwd_vars(char **env, const char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	if (update_env_var(env, "PWD", cwd) != 0)
		return (1);
	if (oldpwd != NULL && update_env_var(env, "OLDPWD", oldpwd) != 0)
		return (1);
	return (0);
}

int	add_env_var(char **env, char *new_entry)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	while (env[i] != NULL)
		i++;
	new_environ = malloc((i + 2) * sizeof(char *));
	if (!new_environ)
	{
		perror("malloc");
		free(new_entry);
		return (1);
	}
	j = 0;
	while (j < i)
	{
		new_environ[j] = env[j];
		j++;
	}
	new_environ[i] = new_entry;
	new_environ[i + 1] = NULL;
	env = new_environ;
	return (0);
}

void	safe_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
