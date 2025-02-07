/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/07 13:32:11 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_builtin(char **cmd, char **env)
{
	if (!ft_strncmp(*cmd, "env", ft_strlen(*cmd)))
		exec_env(env);
	else if (!ft_strncmp(*cmd, "pwd", ft_strlen(*cmd)))
		exec_pwd(cmd);
	exit (0);
}

void	search_builtins(t_data inp)
{
	struct dirent	*entry;
	DIR				*builtins_dir;
	char			*obj;
	char			*path;

	obj = ft_strjoin(*inp.redir.cmd, ".o");
	path = ft_strjoin(inp.home_dir, "/obj/");
	builtins_dir = opendir(path);
	if (!builtins_dir)
	{
		perror("Builtins failed");
		exit (errno);
	}
	entry = readdir(builtins_dir);
	while (entry)
	{
		if (!ft_strncmp(obj, entry->d_name, ft_strlen(*inp.redir.cmd)))
			return (closedir(builtins_dir), free(obj), free(path), exec_builtin(inp.redir.cmd, inp.env));
		entry = readdir(builtins_dir);
	}
	return (closedir(builtins_dir), free(obj), free(path));
}
