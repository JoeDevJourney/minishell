/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/24 18:06:06 by dchrysov         ###   ########.fr       */
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

/**
 * @brief Checks if there's a hanging command near an operator
 * 
 * @param str The address of the input as a str
 * @param dl The operator as a delimeter 
 */
bool	valid_oper(char **str, char *dl)
{
	char	**arr;
	char	*ptr;
	char	*cmd;
	int		i;
	int		size;

	arr = ft_split2(*str, dl);
	size = count_array_size(arr);
	i = -1;
	while (++i < size - 1)
		if (*ft_strtrim(arr[i], " ") == '\0')
			return (printf("syntax error near unexpected token `%s'\n", dl), 0);
	if (*ft_strtrim(arr[i], " ") == '\0')
	{
		cmd = readline("> ");
		while (!*cmd)
			cmd = readline("> ");
		ptr = ft_strjoin(*str, cmd);
		free(*str);
		*str = ft_strdup(ptr);
		free(ptr);
		free(cmd);
	}
	return (free_array(arr), 1);
}
