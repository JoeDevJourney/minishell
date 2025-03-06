/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 17:44:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Concatenates name and value with '=' in between
 */
static char	*create_env_entry(char *name, char *value)
{
	char	*new_entry;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_entry = malloc(len);
	if (!new_entry)
		exit_with_error("cd: malloc failed\n", EXIT_FAILURE);
	ft_strlcpy(new_entry, name, len);
	if (value)
	{
		ft_strlcat(new_entry, "=", len);
		ft_strlcat(new_entry, value, len);
	}
	return (new_entry);
}

/**
 * @brief Checks the env for 'name' and updates its value
 * 
 * @returns 0 upon succcessful replacement, -1 otherwise
 */
static int	replace_env_var(char **env, char *name, char *new_entry)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 \
			&& env[i][ft_strlen(name)] == '=')
		{
			free(env[i]);
			env[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (-1);
}

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
	*env = new_environ;						// free first???
	return (0);
}

/**
 * @brief Adds a new element in the env list if it doesn't already exist,
 * otherwise it replaces its value.
 */
int	update_env_var(char ***env, char *name, char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (1);
	if (replace_env_var(*env, name, new_entry) == 0)
		return (0);
	if (add_env_var(env, new_entry) != 0)
		return (1);
	return (0);
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
