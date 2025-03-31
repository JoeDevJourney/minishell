/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:11:46 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 15:36:09 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (perror("0 bytes"), NULL);
	ptr = malloc(size);
	if (!ptr)
		exit_with_error("Memory allocation failed", EXIT_FAILURE);
	return (ptr);
}

/**
 * @brief Counts the number of words in a str based on the number of occurences
 * of the delimeter
 */
static size_t	num_substr(const char *s, const char *delim)
{
	size_t	count;
	int		i;
	bool	open_sq;
	bool	open_dq;

	count = 1;
	open_sq = false;
	open_dq = false;
	i = -1;
	while (s[++i])
	{
		check_quote(s[i], &open_sq, &open_dq);
		if (!open_sq && !open_dq && ft_strnstr(s, delim, ft_strlen(&s[i])))
			count++;
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
char	**ft_split2(const char *s, const char *del)
{
	const char	*start = s;
	char		**res;
	size_t		i;
	bool		open_sq;
	bool		open_dq;

	i = 0;
	open_sq = false;
	open_dq = false;
	res = safe_malloc((num_substr(s, del) + 1) * sizeof(char *));
	while (*s)
	{
		check_quote(*s, &open_sq, &open_dq);
		if (!open_sq && !open_dq && !ft_strncmp(s, del, ft_strlen(del)))
		{
			res[i++] = ft_substr(start, 0, s - start);
			s += ft_strlen(del);
			start = s;
			continue ;
		}
		s++;
	}
	res[i++] = ft_substr(start, 0, s - start);
	res[i] = NULL;
	return ((char **)res);
}
