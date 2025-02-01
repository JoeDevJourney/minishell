/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 17:06:28 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_builtin(char **cmd, char **env)
{
	if (!ft_strncmp(*cmd, "env", 3))
		return (exec_env(env));
	else if (!ft_strncmp(*cmd, "pwd", 3))
		return (exec_pwd(cmd, env));
	return (0);
}

int	search_builtins(char **cmd, char **env)
{
	struct dirent	*entry;
	DIR				*builtins_dir;
	char 			*obj;
	char 			*path;

	obj = ft_strjoin(*cmd, ".o");
	path = ft_strjoin(getenv("PWD"), "/obj/");			// This won't work when exec a builtin from a
	builtins_dir = opendir(path);						// dir different than the project's home.
	if (!builtins_dir)
	{
		perror("Builtins failed\n");
		return (errno);
	}
	entry = readdir(builtins_dir);
	while (entry)
	{
		if (!ft_strncmp(obj, entry->d_name, ft_strlen(*cmd)))
			return(exec_builtin(cmd, env));
		entry = readdir(builtins_dir);
	}
	closedir(builtins_dir);
	return (-2);
}
