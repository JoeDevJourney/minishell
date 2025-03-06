/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 15:40:00 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

static char	*process_argument(t_data inp)
{
	char	*dir;
	char	*home;

	if (!ft_strncmp(inp.tok[1], "-", 1) && ft_strlen(inp.tok[1]) == 1)
	{
		dir = get_oldpwd_dir(inp);
		if (dir)
		{
			printf("%s\n", dir);
			dir = ft_strdup(dir);
		}
		return (dir);
	}
	if (inp.tok[1][0] == '~')
	{
		home = get_home_dir(inp);
		if (!home)
			return (NULL);
		dir = ft_strjoin(home, inp.tok[1] + 1);
		return (dir);
	}
	if (inp.tok[1][0] == '\0')
		return (NULL);
	return (ft_strdup(inp.tok[1]));
}

char	*get_target_dir(t_data inp)
{
	char	*home;

	if (!inp.tok[1])
	{
		home = get_home_dir(inp);
		if (home)
			return (ft_strdup(home));
		return (NULL);
	}
	return (process_argument(inp));
}

char	*get_home_dir(t_data inp)
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

int	ft_cd(t_data *inp)
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
