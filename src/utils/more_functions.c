/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:11:46 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/27 11:45:32 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Duplicates a len size str starting from *start
 */
static char	*substr_dup(const char *start, size_t len)
{
	char	*substr;

	substr = safe_malloc(len + 1);
	ft_strlcpy(substr, start, len + 1);
	substr[len] = '\0';
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
size_t	count_delim(const char *s, const char *delim)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (ft_strnstr(s, delim, ft_strlen(s)))
			count++;
		s++;
	}
	return (count);
}

/**
 * @brief Works in the same way as the original split, with the diff now being
 * that the delimeter is a char* instead of a char.
 */
char	**ft_split2(const char *s, const char *delim)
{
	char		**res;
	const char	*start = s;
	size_t		i;
	bool		open_sq;
	bool		open_dq;

	i = 0;
	open_sq = false;
	open_dq = false;
	res = safe_malloc((count_delim(s, delim) + 1) * sizeof(char *));
	while (*s)
	{
		if (*s == '\'' && !open_dq)
			open_sq = !open_sq;
		else if (*s == '"' && !open_sq)
			open_dq = !open_dq;
		if (!open_sq && !open_dq && !ft_strncmp(s, delim, ft_strlen(delim)))
		{
			res[i++] = substr_dup(start, s - start);
			s += ft_strlen(delim);
			start = s;
			continue ;
		}
		s++;
	}
	return (res[i++] = substr_dup(start, s - start), res[i] = NULL, res);
}
