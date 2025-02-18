/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/18 11:45:51 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(char **cmd, char **env)
{
	if (!ft_strncmp(*cmd, "env", ft_strlen(*cmd)))
		return (exec_env(env));
	else if (!ft_strncmp(*cmd, "pwd", ft_strlen(*cmd)))
		return (exec_pwd(cmd));
	return (1);
}

bool	search_builtins(t_data inp)
{
	struct dirent	*entry;
	DIR				*builtins_dir;
	char			*obj;
	char			*path;

	obj = ft_strjoin(*inp.command, ".o");
	path = ft_strjoin(inp.home_dir, "/obj/");
	builtins_dir = opendir(path);
	if (!builtins_dir)
		exit_with_error("Builtin failed", errno);
	entry = readdir(builtins_dir);
	while (entry)
	{
		if (!ft_strncmp(obj, entry->d_name, ft_strlen(*inp.command)))
			return (closedir(builtins_dir), free(obj), free(path), 1);
		entry = readdir(builtins_dir);
	}
	return (closedir(builtins_dir), free(obj), free(path), 0);
}
