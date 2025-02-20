/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/20 19:27:36 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Executes the builtin command
 */
int	exec_builtin(t_data inp)
{
	if (!ft_strncmp(*inp.command, "env", ft_strlen(*inp.command)))
		return (exec_env(inp.env));
	else if (!ft_strncmp(*inp.command, "pwd", ft_strlen(*inp.command)))
		return (exec_pwd(inp.command));
	else if (!ft_strncmp(*inp.command, "unset", ft_strlen(*inp.command)))
		return (exec_unset(++inp.command, &inp.env));
	else if (!ft_strncmp(*inp.command, "exit", ft_strlen(*inp.command)))
		return (exec_exit(inp.command[1]));
	return (1);
}

/**
 * @brief Searches for the object file of the command in the obj directory
 * 
 * @returns 1 if the obj is found, 0 if not
 */
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
