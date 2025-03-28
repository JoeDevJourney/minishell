	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/21 18:58:23 by dchrysov         ###   ########.fr       */
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
	name = env_var;
	value = ft_strchr(name, '=');
	if (!value)
		return (printf("Error creating env var\n"),
			free_env_list(new_node), NULL);
	*(value)++ = '\0';
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (printf("Error creating env value\n"),
			free_env_list(new_node), NULL);
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
	(*head) = new_env_node(env[i]);
	current = *head;
	while (++i < size)
	{
		current->next = new_env_node(env[i]);
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
