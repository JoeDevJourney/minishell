/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:37:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/08 16:41:58 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int remove_node(char *name, t_env **head)
{
    t_env *current;
    t_env *prev;
    
    current = *head;
    prev = NULL;
    if (!head || !*head || !name)
        return (1);
    while (current)
    {
        if (strcmp(current->name, name) == 0)
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

int exec_unset(char **cmd, t_env **head)
{
	int	i;

	i = 0;
	while (cmd[++i])
		remove_node(cmd[i], head);
	return (0);
}