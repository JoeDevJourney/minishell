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
	t_env	*new_node;
	int		i;

	if (!env || !*env)
		return (perror("env list empty"));
	new_node = new_env_node(env[0]);
	if (!new_node)
		return (perror("malloc failed in new_env_node"));
	*head = new_node;
	current = *head;
	i = 0;
	while (env[++i])
	{
		new_node = new_env_node(env[i]);
		if (!new_node)
		{
			perror("malloc failed in new_env_node");
			continue ;
		}
		current->next = new_node;
		current = current-> next;
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
