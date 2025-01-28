/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:05:39 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:13:54 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cat_len;
	size_t	i;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	cat_len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && cat_len < dstsize - 1)
	{
		dst[cat_len] = src[i];
		cat_len++;
		i++;
	}
	dst[cat_len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
