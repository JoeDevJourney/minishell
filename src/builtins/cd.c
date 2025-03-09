/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/09 22:01:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Adds the new entry to the env list.
 */
static void	add_env_var(char ***env, char *new_entry)
{
	int		j;
	int		size;
	char	**new_environ;

	size = count_array_size(*env);
	new_environ = safe_malloc((size + 2) * sizeof(char *));
	j = -1;
	while ((*env)[++j])
		new_environ[j] = ft_strdup((*env)[j]);
	new_environ[j++] = ft_strdup(new_entry);
	new_environ[j] = NULL;
	free_array(*env);
	*env = new_environ;
}

static char	*create_env_entry(const char *name, const char *value)
{
	char	*new_entry;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 1;
	new_entry = safe_malloc(len + 1);
	ft_strlcpy(new_entry, name, len + 1);
	ft_strlcat(new_entry, "=", len + 1);
	ft_strlcat(new_entry, value, len + 1);
	return (new_entry);
}

static bool	replace_env_var(char ***env, const char *name, char *new_entry)
{
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, ft_strlen(name)) == 0 \
			&& (*env)[i][ft_strlen(name)] == '=')
		{
			(*env)[i] = new_entry;
			return (true);
		}
		i++;
	}
	return (false);
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
	if (replace_env_var(env, name, new_entry))
		return (0);
	add_env_var(env, new_entry);
	free(new_entry);
	return (0);
}

int	exec_cd(t_data *inp)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = ft_strdup(get_env_val(inp->env_node, "PWD"));
	dir = get_target_dir(*inp);
	if (!dir || chdir(dir) != 0)
		return (perror(dir), 1);
	// if (oldpwd && update_env_var(&inp->env, "OLDPWD", oldpwd) != 0)
	// 	return (1);
	if (update_pwd_vars(&inp->env, oldpwd) != 0)
		return (1);
	free(dir);
	free(oldpwd);
	return (0);
}
