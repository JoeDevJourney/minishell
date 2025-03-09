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

void	dupl_env(char ***arr, char **env)
{
	int	i;
	int	size;

	size = count_array_size(env);
	*arr = safe_malloc((size + 1) * sizeof(char *));
	i = -1;
	while (++i < size)
	{
		(*arr)[i] = ft_strdup(env[i]);
		if (!(*arr)[i])
		{
			free_array(*arr);
			return ;
		}
	}
	(*arr)[i] = NULL;
}

static void	free_env_list(t_env *head)
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

static void	split_env_var(char *env_var, char **name, char **value)
{
	char *equal_sign;

	equal_sign = strchr(env_var, '=');
	if (!equal_sign)
	{
		*name = strdup(env_var);
		*value = NULL;
		return ;
	}
	*name = strndup(env_var, equal_sign - env_var);
	*value = strdup(equal_sign + 1);
}

static t_env	*new_env_node(char *env_var)
{
	t_env	*new_node;

	new_node = safe_malloc(sizeof(t_env));
	split_env_var(env_var, &new_node->name, &new_node->value);
	if (!new_node->name)
		return (free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

t_env	*dupl_env2(char **env)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (env[i])
	{
		new_node = new_env_node(env[i]);
		if (!new_node)
			return (free_env_list(head), NULL);
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
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
