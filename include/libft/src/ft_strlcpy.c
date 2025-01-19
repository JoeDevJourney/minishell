/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:23:10 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:14:00 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	cpy_len;

	i = 0;
	if (size <= 0)
		return (ft_strlen(src));
	if (size <= ft_strlen(src))
		cpy_len = size - 1;
	else
		cpy_len = ft_strlen(src);
	while (i < cpy_len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
