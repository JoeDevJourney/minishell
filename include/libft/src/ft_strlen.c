/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:03:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/28 16:17:22 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

unsigned long	ft_strlen(const char str[])
{
	const char		*ptr;
	unsigned long	len;

	if (!str)
		return (0);
	ptr = str;
	len = 0;
	if (str)
	{
		while (*ptr)
		{
			len++;
			ptr++;
		}
	}
	return (len);
}
