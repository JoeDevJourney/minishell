/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:11:46 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 13:03:57 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Counts the number of words in a str based on the number of occurences
 * of the delimeter
 */
static size_t	num_substr(const char *s, const char *delim)
{
	size_t	count;

	count = 1;
	while (*s)
	{
		if (ft_strnstr(s, delim, ft_strlen(s)))
			count++;
		s++;
	}
	return (count);
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
 * @brief Works in the same way as the original split, with the diff now being
 * that the delimeter is a char* instead of a char.
 */
static char	*ftstrndp(const char *start, size_t len)
{
	char	*substr;

	substr = safe_malloc(len + 1);
	ft_strlcpy(substr, start, len + 1);
	substr[len] = '\0';
	return (substr);
}

char	**ft_split2(const char *s, const char *del)
{
	const char	*start = s;
	const char	**res = safe_malloc((num_substr(s, del) + 1) * sizeof(char *));
	size_t		i;
	bool		open_sq;
	bool		open_dq;

	i = 0;
	open_sq = false;
	open_dq = false;
	while (*s)
	{
		if (*s == '\'' && !open_dq)
			open_sq = !open_sq;
		else if (*s == '"' && !open_sq)
			open_dq = !open_dq;
		if (!open_sq && !open_dq && ft_strncmp(s, del, ft_strlen(del)) == 0)
		{
			res[i++] = ftstrndp(start, s - start);
			s += ft_strlen(del);
			start = s;
			continue ;
		}
		s++;
	}
	return (res[i++] = ftstrndp(start, s - start), res[i] = NULL, (char **)res);
}
