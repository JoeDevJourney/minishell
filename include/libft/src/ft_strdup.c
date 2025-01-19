/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:15:16 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:13:38 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memmove(ptr, s, (size_t)ft_strlen(s) + 1);
	return (ptr);
}
