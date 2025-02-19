/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/19 15:36:12 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit_with_error("Memory allocation failed", EXIT_FAILURE);
	return (ptr);
}

/**
 * @brief Returns the relative wd
 * @note Used when printing the terminal prompt.
 */
char	*rwd(char *dir)
{
	char	*ptr;

	ptr = dir;
	ptr += ft_strlen(dir) - 1;
	while (ptr-- && *ptr != '/')
		ptr--;
	return (++ptr);
}

/**
 * @brief Searches the **arr for the '$' to replace the environmental key
 * with its corresponding value
 */
void	expansion_oper(char **arr)
{
	char	**ptr;
	char	*val;

	ptr = arr;
	while (*ptr)
	{
		if (ft_strchr(*ptr, '$'))
		{
			val = getenv(ft_strchr(*ptr, '$') + 1);
			free(*ptr);
			if (val)
				*ptr = ft_strdup(val);
			else
				*ptr = NULL;
		}
		ptr++;
	}
}

t_env_var	*create_env_node(char **cmd)
{
	t_env_var	*node;

	node = safe_malloc(sizeof(t_env_var));
	node->name = ft_strdup(cmd[0]);
	node->value = ft_strdup(cmd[1]);
	node->next = NULL;
	return (node);	
}

void	dupl_env(t_data *inp, char **env)
{
	size_t		i;
	size_t		size;
	t_env_var	*ptr;
	char		**arr;

	i = 0;
	size = count_array_size(env);
	arr = ft_split(env[i], '=');
	inp->nvp = create_env_node(arr);
	free_array(arr);
	ptr = inp->nvp;
	while (++i < size)
	{
		arr = ft_split(env[i], '=');
		ptr->next = create_env_node(arr);
		ptr = ptr->next;
		free_array(arr);
	}
}
