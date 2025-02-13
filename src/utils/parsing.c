/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/13 18:10:39 by dchrysov         ###   ########.fr       */
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

/**
 * @brief Adds elements to an already existing array of strings 
 */
char	**add_to_array(char **arr, char *new_str)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = safe_malloc((i + 2) * sizeof(char *));
	i = 0;
	while (arr && arr[i])
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}

/**
 * @brief Scans the input for every redirection operator and stores the fd
 * in the appropriate array.
 */
// void	parse_redir(t_data *inp)
// {
// 	char	**tok;
// 	int		i;

// 	tok = ft_split(*inp->pipe.cmd, ' ');
// 	inp->out_op.cmd = NULL;
// 	inp->inp_op.cmd = NULL;
// 	inp->app_op.cmd = NULL;
// 	inp->hdoc_op.cmd = NULL;
// 	i = -1;
// 	while (tok[++i])
// 	{
// 		if (!ft_strncmp(tok[i], "<", ft_strlen(tok[i])) && tok[i + 1])
// 			inp->inp_op.cmd = add_to_array(inp->inp_op.cmd, tok[i + 1]);
// 		else if (!ft_strncmp(tok[i], ">", ft_strlen(tok[i])) && tok[i + 1])
// 			inp->out_op.cmd = add_to_array(inp->out_op.cmd, tok[i + 1]);
// 		else if (!ft_strncmp(tok[i], ">>", ft_strlen(tok[i])) && tok[i + 1])
// 			inp->app_op.cmd = add_to_array(inp->app_op.cmd, tok[i + 1]);
// 		else if (!ft_strncmp(tok[i], "<<", ft_strlen(tok[i])) && tok[i + 1])
// 			inp->hdoc_op.cmd = add_to_array(inp->hdoc_op.cmd, tok[i + 1]);
// 	}
// 	free_array(tok);
// }
