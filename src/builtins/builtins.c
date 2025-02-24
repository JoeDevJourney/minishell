/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/21 17:50:52 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Executes the builtin command
 */
int	exec_builtin(char **cmd, char ***env)
{
	if (!ft_strncmp(*cmd, "env", 3) && ft_strlen(*cmd) == 3)
		return (exec_env(*env));
	else if (!ft_strncmp(*cmd, "pwd", 3) && ft_strlen(*cmd) == 3)
		return (exec_pwd(cmd));
	else if (!ft_strncmp(*cmd, "cd", 2) && ft_strlen(*cmd) == 2)
		return (ft_cd(env, cmd));
	else if (!ft_strncmp(*cmd, "unset", 5) && ft_strlen(*cmd) == 5)
		return (exec_unset(++cmd, env));
	else if (!ft_strncmp(*cmd, "exit", 4) && ft_strlen(*cmd) == 4)
		return (exec_exit(cmd[1]));
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
		if (!ft_strncmp(obj, entry->d_name, ft_strlen(obj))
			&& entry->d_name[ft_strlen(obj)] == '\0')
			return (closedir(builtins_dir), free(obj), free(path), 1);
		entry = readdir(builtins_dir);
	}
	return (closedir(builtins_dir), free(obj), free(path), 0);
}
