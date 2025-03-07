/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:37:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/07 10:20:37 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Removes the index line from the array
 */
static void	remove_line(char ***env, int index)
{
	char	**new_arr;
	int		size;
	int		i;
	int		j;

	size = count_array_size(*env);
	if (index < 0 || index >= size)
		return ;
	new_arr = safe_malloc(size * sizeof(char *));
	free((*env)[index]);
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (i != index)
		{
			new_arr[j] = (*env)[i];
			j++;
		}
	}
	new_arr[j] = NULL;
	free(*env);
	*env = new_arr;
}

/**
 * @brief Searches for *cmd in the **env
 * 
 * @returns The index of the variable found in **env (-1 if not found) 
 */
static int	var_index(char *cmd, char **env)
{
	char	**tok;
	int		len;
	int		i;

	i = -1;
	while (env[++i])
	{
		tok = ft_split(env[i], '=');
		len = ft_strlen(cmd);
		if (!ft_strncmp(cmd, *tok, len) && tok[0][len] == '\0')
			return (free_array(tok), i);
		free_array(tok);
	}
	return (-1);
}

int	exec_unset(char **cmd, char ***env)
{
	int	i;

	i = 0;
	if (!cmd[i])
		return (0);
	if (cmd[i][0] == '-')
	{
		if (ft_strncmp(cmd[i], "-v", ft_strlen(cmd[i]))
			&& ft_strlen(cmd[i]) == 2)
			return (printf("bash: unset: %s: invalid option\n", cmd[i]), 2);
		i++;
	}
	while (cmd[i])
		remove_line(env, var_index(cmd[i++], *env));
	return (0);
}
