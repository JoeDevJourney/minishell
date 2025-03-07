/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/07 18:44:10 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Adds the new entry to the env list.
 */
static int	add_env_var(char ***env, char *new_entry)
{
	int		i;
	int		j;
	char	**new_environ;

	i = 0;
	while ((*env)[i] != NULL)
		i++;
	new_environ = safe_malloc((i + 2) * sizeof(char *));
	j = -1;
	while (++j < i)
		new_environ[j] = (*env)[j];
	new_environ[i] = new_entry;
	new_environ[i + 1] = NULL;
	free_array(*env);
	*env = new_environ;
	return (0);
}

static int	update_pwd_vars(char ***env, char *oldpwd)
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

/**
 * @brief Adds a new element in the env list if it doesn't already exist,
 * otherwise it replaces its value.
 */
int	update_env_var(char ***env, char *name, char *value)
{
	char	*new_entry;
	int		i;
	int		name_len;

	name_len = ft_strlen(name);
	new_entry = ft_strjoin3(name, "=", value);
	if (!new_entry)
		return (1);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, name_len) == 0 &&
			(*env)[i][name_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (add_env_var(env, new_entry));
}

int	exec_cd(t_data *inp)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = get_env_val(*inp, "PWD");
	dir = get_target_dir(*inp);
	if (!dir || chdir(dir) != 0)
		return (perror(dir), 1);
	if (oldpwd && update_env_var(&inp->env, "OLDPWD", oldpwd) != 0)
		return (1);
	if (update_pwd_vars(&inp->env, oldpwd) != 0)
		return (1);
	free(dir);
	return (0);
}
