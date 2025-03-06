/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 14:53:33 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*create_env_entry(const char *name, const char *value)
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

static int	replace_env_var(char **env, const char *name, char *new_entry)
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

int	update_env_var(char ***env, const char *name, const char *value)
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

int	ft_cd(t_data *inp)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = get_env_val(*inp, "PWD");
	dir = get_target_dir(*inp);
	if (!dir || chdir(dir) != 0)
		return (perror("cd"), 1);
	if (oldpwd && update_env_var(&inp->env, "OLDPWD", oldpwd) != 0)
		return (1);
	if (update_pwd_vars(&inp->env, oldpwd) != 0)
		return (1);
	free(dir);
	return (0);
}
