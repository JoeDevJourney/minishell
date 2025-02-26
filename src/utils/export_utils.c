/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:47:46 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/26 18:28:01 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
