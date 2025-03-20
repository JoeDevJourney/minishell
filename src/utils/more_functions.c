/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:11:46 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/20 16:08:16 by dchrysov         ###   ########.fr       */
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

void	exit_with_error(char *msg, int ret_val)
{
	perror(msg);
	exit(ret_val);
}

/**
 * @brief Returns the size of an array of strings 
 */
size_t	count_array_size(char **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
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

	if (!s || !delim || !*delim)
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
	size_t		delim_len;
	size_t		i;
	bool		open_sq;
	bool		open_dq;

	i = 0;
	start = s;
	delim_len = ft_strlen(delim);
	open_sq = false;
	open_dq = false;
	if (!s || !delim || *s == '\0')
		return (NULL);
	result = safe_malloc((count_substr(s, delim) + 1) * sizeof(char *));
	while (*s)
	{
		if (*s == '\'' && !open_dq)
			open_sq = !open_sq;
		else if (*s == '"' && !open_sq)
			open_dq = !open_dq;
		if (!open_sq && !open_dq && !ft_strncmp(s, delim, delim_len))
		{
			result[i++] = substr_dup(start, s - start);
			s += delim_len;
			start = s;
			continue ;
		}
		s++;
	}
	result[i++] = ft_strdup(start);
	result[i] = NULL;
	return (result);
}
