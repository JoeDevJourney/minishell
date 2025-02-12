/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/12 15:48:53 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_builtin(char **cmd, char **env)
{
	if (!ft_strncmp(*cmd, "env", ft_strlen(*cmd)))
		exec_env(env);
	else if (!ft_strncmp(*cmd, "pwd", ft_strlen(*cmd)))
		exec_pwd(cmd);
}

bool	search_builtins(t_data inp)
{
	struct dirent	*entry;
	DIR				*builtins_dir;
	char			*obj;
	char			*path;

	obj = ft_strjoin(*inp.redir.cmd, ".o");
	path = ft_strjoin(inp.home_dir, "/../obj/");
	builtins_dir = opendir(path);
	if (!builtins_dir)
		exit_with_error("Builtin failed", errno);
	entry = readdir(builtins_dir);
	while (entry)
	{
		if (!ft_strncmp(obj, entry->d_name, ft_strlen(*inp.redir.cmd)))
		{
			free(obj);
			obj = NULL;
			return (closedir(builtins_dir), free(obj), free(path),
				exec_builtin(inp.redir.cmd, inp.env), 1);
		}
		entry = readdir(builtins_dir);
	}
	return (closedir(builtins_dir), free(obj), free(path), 0);
}
