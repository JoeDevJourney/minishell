/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:02:02 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/21 14:07:17 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	str_count(char const *s, char c)
{
	size_t	res;
	int		in_word;

	res = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			res++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (res);
}

static char	*ft_next_word(char const **s, char c)
{
	char const	*start;
	char		*str;
	size_t		len;

	while (**s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	len = *s - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, start, len + 1);
	return (str);
}

static void	free_split(char **table, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(table[i]);
		i++;
	}
	free(table);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = str_count(s, c);
	res = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		res[i] = ft_next_word(&s, c);
		if (!res[i])
		{
			free_split(res, i);
			return (NULL);
		}
		i++;
	}
	res[word_count] = NULL;
	return (res);
}
