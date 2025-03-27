/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/27 19:18:53 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Merges two array of strings together
 * 
 * @param src The src array to be expanded after merging
 * @param dst The dest array to be merged with src
 * @param dst_size The size of the dest array
 * 
 * @note If src is NULL it will still merge it with dest, resulting
 * to its duplication
 */
static void	merge_arrays(char ***src, char **dst, size_t dst_size)
{
	size_t	src_size;
	size_t	total_size;
	char	**new_dst;
	size_t	i;
	size_t	j;

	src_size = count_array_size(*src);
	total_size = src_size + dst_size;
	new_dst = safe_malloc((total_size + 1) * sizeof(char *));
	i = -1;
	while (++i < src_size)
		new_dst[i] = (*src)[i];
	j = 1;
	while (dst[j])
		new_dst[i++] = ft_strdup(dst[j++]);
	new_dst[i] = NULL;
	free(*src);
	*src = new_dst;
}

/**
 * @brief Scans an array of strings for operators, and stores the according
 * commands in the appropriate places.
 * 
 * @param str The array to be searched for operators and splitted if necessary
 * @param rest Array of arrays of strings where the found cmds would be stored
 * @param split_arr Contains the tokens obtained from splitting
 */
static void	split_and_store(char **str, char ***rest, char *del)
{
	char	**split_arr;
	size_t	new_count;

	if (!str || !*str || !del)
		return ;
	split_arr = ft_split2(*str, del);
	if (!split_arr)
		return ;
	free(*str);
	*str = ft_strdup(split_arr[0]);
	new_count = count_array_size(split_arr) - 1;
	if (new_count > 0)
		merge_arrays(rest, split_arr, new_count);
	free_array(split_arr);
}

/**
 * @brief Init an array with the redir oper symbols and groups all the according
 * arrays to one single array of arrays of strings.
 */
static void	init_lists_and_del(t_data *inp, char ****lists, char **del)
{
	del[0] = "<<";
	del[1] = ">>";
	del[2] = "<";
	del[3] = ">";
	lists[0] = &(inp->hdoc_op.cmd);
	lists[1] = &(inp->app_op.cmd);
	lists[2] = &(inp->inp_op.cmd);
	lists[3] = &(inp->out_op.cmd);
}

/**
 * @brief Trims all the redirection oper arrays of any leading or ending spaces 
 */
static bool	trim_spaces(t_data *inp)
{
	char	**arr[5];
	char	*trimmed;
	size_t	size;
	size_t	i;

	arr[0] = inp->pipe.cmd;
	arr[1] = inp->inp_op.cmd;
	arr[2] = inp->out_op.cmd;
	arr[3] = inp->app_op.cmd;
	arr[4] = inp->hdoc_op.cmd;
	i = -1;
	while (++i < 5)
	{
		size = count_array_size(arr[i]) + 1;
		while (--size > 0)
		{
			if (*arr[i][0] == '\0')
				return (printf("syntax error near unexpected token"
						" `newline'\n"), inp->ret_val = 258, false);
			trimmed = ft_strtrim(arr[i][size - 1], " ");
			free(arr[i][size - 1]);
			arr[i][size - 1] = trimmed;
		}
	}
	return (true);
}

/**
 * @brief Scans the input for any redirerction operators and saves them in the
 * appropriate array
 * 
 * @note (char *)inp->cmd: input command
 * @note (char **)inp->tok: output command
 */
bool	parse_redir(t_data *inp)
{
	char	***lists[4];
	char	*del[4];
	char	**ptr;
	int		i;
	int		j;

	init_lists_and_del(inp, lists, del);
	j = -1;
	while (++j < 4)
		split_and_store(&inp->cmd, lists[j], del[j]);
	i = -1;
	while (++i < 4)
	{
		ptr = *lists[i];
		while (ptr && *ptr)
		{
			j = -1;
			while (++j < 4)
				split_and_store(ptr, lists[j], del[j]);
			ptr++;
		}
	}
	return (trim_spaces(inp));
}
