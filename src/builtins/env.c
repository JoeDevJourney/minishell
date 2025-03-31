/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 14:42:23 by jbrandt          ###   ########.fr       */
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
	char	*equal_sign;
	char	*name;
	char	*value;

	if (!env_var)
		return (printf("Error: NULL env_var\n"), NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
		return (printf("Error: Invalid env_var format\n"), NULL);
	new_node = safe_malloc(sizeof(t_env));
	name = ft_substr(env_var, 0, equal_sign - env_var);
	if (!name)
		return (printf("Error: substr failed for name\n"),
			free_env_list(new_node), NULL);
	value = ft_strdup(equal_sign + 1);
	if (!value)
		return (printf("Error: strdup failed for value\n"),
			free(name), free_env_list(new_node), NULL);
	new_node->name = name;
	new_node->value = value;
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
