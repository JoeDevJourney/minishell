/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:27:01 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:11:44 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*d;
	const unsigned char		*s;
	size_t					i;

	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < len)
	{
		if (d < s)
		{
			d[i] = s[i];
			i++;
		}
		else
		{
			d[len - i - 1] = s[len - i - 1];
			i ++;
		}
	}
	return (dst);
}
