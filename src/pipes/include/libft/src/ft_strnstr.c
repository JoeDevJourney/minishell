/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:47:27 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:14:21 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (*little == '\0')
		return ((char *)big);
	while (*big && len >= ft_strlen(little))
	{
		if (*big == *little)
		{
			if (ft_strncmp(big, little, ft_strlen(little)) == 0)
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (NULL);
}
