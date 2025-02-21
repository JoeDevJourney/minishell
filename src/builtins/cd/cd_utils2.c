/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:15:14 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/21 18:33:13 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	update_pwd_vars(char ***env, const char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	if (oldpwd && update_env_var(env, "OLDPWD", oldpwd) != 0)
		return (1);
	if (update_env_var(env, "PWD", cwd) != 0)
		return (1);
	return (0);
}

int	add_env_var(char ***env, char *new_entry)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	while ((*env)[i] != NULL)
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
		new_environ[j] = (*env)[j];
		j++;
	}
	new_environ[i] = new_entry;
	new_environ[i + 1] = NULL;
	*env = new_environ;
	return (0);
}

static char	*process_argument(char *arg, char **env)
{
	char	*dir;
	char	*home;

	if (ft_strcmp(arg, "-") == 0)
	{
		dir = get_oldpwd_dir(env);
		if (dir)
		{
			printf("%s\n", dir);
			dir = ft_strdup(dir);
		}
		return (dir);
	}
	if (arg[0] == '~')
	{
		home = get_home_dir(env);
		if (!home)
			return (NULL);
		dir = ft_strjoin(home, arg + 1);
		return (dir);
	}
	if (arg[0] == '\0')
		return (NULL);
	return (ft_strdup(arg));
}

char	*get_target_dir(char **args, char **env)
{
	char	*home;

	if (args[1] && args[2])
		return (NULL);
	if (!args[1])
	{
		home = get_home_dir(env);
		if (home)
			return (ft_strdup(home));
		return (NULL);
	}
	return (process_argument(args[1], env));
}
