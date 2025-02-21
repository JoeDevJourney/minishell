/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/21 19:44:39 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit_with_error("Memory allocation failed", EXIT_FAILURE);
	return (ptr);
}

/**
 * @brief Returns the relative wd
 * @note Used when printing the terminal prompt.
 */
char	*rwd(char *dir)
{
	char	*ptr;

	ptr = dir;
	ptr += ft_strlen(dir) - 1;
	while (ptr-- && *ptr != '/')
		ptr--;
	return (++ptr);
}

/**
 * @brief Searches the **arr for the '$' to replace the environmental key
 * with its corresponding value
 */
void	expansion_oper(char **arr)
{
	char	**ptr;
	char	*val;

	ptr = arr;
	while (*ptr)
	{
		if (ft_strchr(*ptr, '$'))
		{
			val = getenv(ft_strchr(*ptr, '$') + 1);
			free(*ptr);
			if (val)
				*ptr = ft_strdup(val);
			else
				*ptr = NULL;
		}
		ptr++;
	}
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

char	*ft_strjoin_free(char *s1, char *s2, int free_flag)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (free_flag & 1)
		free(s1);
	if (free_flag & 2)
		free(s2);
	return (result);
}
