/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/05 12:01:55 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Executes the builtin command
 * 
 * @note For commands like echo/export we need the argument in its unmodified
 * status, so we use *inp.pipe.cmd
 */
int	exec_builtin(t_data *inp)
{
	if (!ft_strncmp(*inp->tok, "env", 3) && ft_strlen(*inp->tok) == 3)
		return (exec_env(inp->env));
	else if (!ft_strncmp(*inp->tok, "pwd", 3)
		&& ft_strlen(*inp->tok) == 3)
		return (exec_pwd(inp->tok));
	else if (!ft_strncmp(*inp->tok, "cd", 2)
		&& ft_strlen(*inp->tok) == 2)
		return (ft_cd(&inp->env, inp->tok));
	else if (!ft_strncmp(*inp->tok, "export", 6)
		&& ft_strlen(*inp->tok) == 6)
		return (ft_export(inp->pipe.cmd[0], &inp->env));
	else if (!ft_strncmp(*inp->tok, "unset", 5)
		&& ft_strlen(*inp->tok) == 5)
		return (exec_unset(inp->tok + 1, &inp->env));
	else if (!ft_strncmp(*inp->tok, "exit", 4)
		&& ft_strlen(*inp->tok) == 4)
		return (exec_exit(inp->tok[1]));
	return (exec_echo(inp->tok));
	return (0);
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

	obj = ft_strjoin(*inp.tok, ".o");
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
