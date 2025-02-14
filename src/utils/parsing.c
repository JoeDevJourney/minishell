/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/14 12:35:11 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*substr_dup(const char *start, size_t len)
{
	char	*substr;

	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, start, len);
	return (substr);
}

/**
 * @brief Counts the number of words in a str based on the number of occurences
 * of the delimeter
 */
size_t	count_substr(const char *s, const char *delim)
{
	size_t		count;
	const char	*tmp;
	size_t		delim_len;

	if (!s || !delim || *delim == '\0')
		return (0);
	count = 0;
	tmp = s;
	delim_len = ft_strlen(delim);
	tmp = ft_strnstr(tmp, delim, ft_strlen(tmp));
	while (tmp)
	{
		count++;
		tmp += delim_len;
		tmp = ft_strnstr(tmp, delim, ft_strlen(tmp));
	}
	if (*s != '\0')
		count++;
	return (count);
}

/**
 * @brief Works in the same way as the original split, with the diff now being
 * that the delimeter is a char* instead of a char.
 */
char	**ft_split2(const char *s, const char *delim)
{
	char		**result;
	const char	*start;
	const char	*end;
	size_t		delim_len;
	size_t		i;

	i = 0;
	start = s;
	delim_len = ft_strlen(delim);
	end = ft_strnstr(start, delim, ft_strlen(start));
	if (!s || !delim)
		return (NULL);
	result = (char **)malloc((count_substr(s, delim) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (end)
	{
		result[i++] = substr_dup(start, end - start);
		start = end + delim_len;
		end = ft_strnstr(start, delim, ft_strlen(start));
	}
	result[i++] = ft_strdup(start);
	result[i] = NULL;
	return (result);
}
