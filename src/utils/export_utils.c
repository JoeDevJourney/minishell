/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:47:46 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/25 18:54:35 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_name(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_identifier(const char *str)
{
	const char	*ptr;
	int			has_equal;

	has_equal = 0;
	ptr = str;
	if (!str || !*str)
		return (0);
	while (*ptr && *ptr != '=')
		ptr++;
	if (*ptr == '=')
		has_equal = 1;
	if (has_equal)
		return (is_valid_name(str));
	return (is_valid_name(str));
}

char	**ft_arrdup(char **arr, int size)
{
	char	**copy;
	int		i;

	copy = malloc(size * sizeof(char *));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < size - 1 && arr[i])
		copy[i] = ft_strdup(arr[i]);
	copy[i] = NULL;
	return (copy);
}

void	ft_arrfree(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	ft_swap(void *a, void *b, size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(temp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, temp, size);
	free(temp);
}
