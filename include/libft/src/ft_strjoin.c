/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:52:55 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:13:49 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*concat_str;

	concat_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!concat_str)
		return (NULL);
	ft_strlcpy(concat_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(concat_str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (concat_str);
}
