/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:55:32 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:11:36 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ptr1;
	const char	*ptr2;
	size_t		i;

	ptr1 = (const char *)s1;
	ptr2 = (const char *)s2;
	i = 0;
	while (i < n)
	{
		if (*ptr1 != *ptr2)
			return (*(unsigned char *)ptr1 - *(unsigned char *)ptr2);
		ptr1++;
		ptr2++;
		i++;
	}
	return (0);
}
