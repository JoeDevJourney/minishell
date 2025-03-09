/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:53:05 by jbrandt           #+#    #+#             */
/*   Updated: 2024/10/29 10:14:34 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*str_join(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, len1);
	if (s2)
		ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	if (s1)
		free(s1);
	return (result);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = -1;
	if (str == NULL)
		return (NULL);
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (&str[i]);
	}
	return (NULL);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *) src)[i];
		i++;
	}
	return (dst);
}
