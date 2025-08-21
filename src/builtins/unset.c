/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:37:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/21 18:56:21 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Removes a node from the environment list by name.
 * 
 * @param name Variable name to remove.
 * @param head Pointer to head of environment list.
 * @return int 0 if removed, 1 if not found.
 */
static int	remove_node(char *name, t_env **head)
{
	t_env	*current;
	t_env	*prev;

	if (!head || !*head || !name)
		return (1);
	current = *head;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name))
			&& ft_strlen(current->name) == ft_strlen(name))
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

/**
 * @brief Executes the unset builtin, removing variables from environment.
 * 
 * @param cmd Array of command arguments.
 * @param head Pointer to head of environment list.
 * @return int Always 0.
 */
int	exec_unset(char **cmd, t_env **head)
{
	int	i;

	i = 0;
	while (cmd[++i])
		remove_node(cmd[i], head);
	return (0);
}
