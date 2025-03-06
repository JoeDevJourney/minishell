/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:47:46 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 15:15:18 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @returns an allocated copy of arr, given its size
 */
char	**ft_arrdup(char **arr, int size)
{
	char	**copy;
	int		i;

	copy = malloc(size * sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < size - 1 && arr[i])
		copy[i] = ft_strdup(arr[i]);
	copy[i] = NULL;
	return (copy);
}

void	ft_arrfree(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_swap(void *a, void *b, size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
		exit_with_error("malloc error\n", EXIT_FAILURE);
	ft_memcpy(temp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, temp, size);
	free(temp);
}

/**
 * @brief Extracts the env variable from the env list.
 */
char	*get_env_val(t_data inp, char *name)
{
	size_t	name_len;
	int		i;

	name_len = ft_strlen(name);
	i = -1;
	if (!ft_strncmp(name, "\?", 1) && name_len == 1)
		return (ft_itoa(inp.ret_val));
	while (inp.env[++i])
		if (!ft_strncmp(inp.env[i], name, name_len)
			&& inp.env[i][name_len] == '=')
			return (&inp.env[i][name_len + 1]);
	return (NULL);
}
