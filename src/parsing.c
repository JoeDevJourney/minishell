/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/23 17:56:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *substr_dup(const char *start, size_t len)
{
    char *substr = (char *)malloc(len + 1);
    if (!substr)
        return (NULL);
    ft_strlcpy(substr, start, len);
    substr[len] = '\0';
    return (substr);
}

size_t count_substr(const char *s, const char *delim)
{
    size_t count = 0;
    const char *tmp = s;
    size_t delim_len;

	delim_len = strlen(delim);
    while ((tmp = ft_strnstr(tmp, delim, ft_strlen(tmp))))
    {
        count++;
        tmp += delim_len;
    }
    return count + 1;
}

/**
 * @brief Works in the same way as the original split, with the diff now being
 * that the delimeter is a char* instead of a char.
 */
char **ft_split2(const char *s, const char *delim)
{
    char **result;
    size_t i;
    size_t delim_len;
    const char *start = s;
    const char *end;

	i = 0;
	delim_len = ft_strlen(delim);
    if (!s || !delim)
        return (NULL);
    result = (char **)malloc((count_substr(s, delim) + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    while ((end = ft_strnstr(start, delim, ft_strlen(start))))
    {
        result[i++] = substr_dup(start, end - start);
        start = end + delim_len;
    }
    result[i++] = ft_strdup(start);
    result[i] = NULL;
    return (result);
}

