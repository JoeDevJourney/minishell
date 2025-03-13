/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 21:51:21 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

t_env	*new_env_node(char *env_var)
{
	t_env	*new_node;
	char	*name;
	char	*value;

	new_node = safe_malloc(sizeof(t_env));
	name = ft_strdup(env_var);
	value = ft_strchr(name, '=');
	if (!value)
		return (perror("Error duplicating env"), NULL);
	*(value)++ = '\0';
	new_node->name = name;
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	dupl_env(t_env **head, char **env)
{
	t_env	*current;
	int		size;
	int		i;

	if (!env || !*env)
		return (perror("env list empty"));
	size = count_array_size(env);	
	i = 0;
	(*head) = new_env_node(env[i++]);
	current = *head;
	while (i < size)
	{
		current->next = new_env_node(env[i++]);
		current = current->next;
	}
}

int	exec_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
	return (0);
}
