/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 16:22:17 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	free_array(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
		free(*temp++);
	free (arr);
	arr = NULL;
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
