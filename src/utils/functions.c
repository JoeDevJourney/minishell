/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/12 12:06:18 by dchrysov         ###   ########.fr       */
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

void	free_array(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
		free(*temp++);
	free (arr);
	arr = NULL;
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

/**
 * @brief Joins together a char **array, creating one ' ' separated char *str.
 */
char	*join_cmd(char **arr)
{
	char	*temp;
	char	*line;
	char	*newline;

	temp = NULL;
	newline = NULL;
	line = NULL;
	while (*arr)
	{
		temp = ft_strjoin(*arr, " ");
		newline = ft_strjoin(line, temp);
		free(temp);
		free (line);
		line = newline;
		arr++;
	}
	temp = NULL;
	// free(newline);	(?)
	return (line);
}
