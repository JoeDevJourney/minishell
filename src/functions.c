/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 15:47:18 by dchrysov         ###   ########.fr       */
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

char	*rwd(char *dir)
{
	char	*ptr;

	ptr = dir;
	ptr += ft_strlen(dir) - 1;
	while (ptr-- && *ptr != '/')
		ptr--;
	return (++ptr);
}
