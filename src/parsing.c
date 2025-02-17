/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/17 19:45:27 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	merge_rest(char ***rest, char **split_arr, size_t new_count)
{
	size_t	old_count;
	size_t	total_count;
	char	**new_rest;
	size_t	i;
	size_t	j;

	old_count = count_array_size(*rest);
	total_count = old_count + new_count;
	new_rest = safe_malloc((total_count + 1) * sizeof(char *));
	i = -1;
	while (++i < old_count)
		new_rest[i] = (*rest)[i];
	j = 1;
	while (split_arr[j])
		new_rest[i++] = ft_strdup(split_arr[j++]);
	new_rest[i] = NULL;
	free(*rest);
	*rest = new_rest;
}

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
		merge_rest(rest, split_arr, new_count);
	free_array(split_arr);
}

static void	init_lists_and_del(t_data *inp, char ****lists, char **del)
{
	del[0] = "<<";
	del[1] = ">>";
	del[2] = "<";
	del[3] = ">";
	lists[0] = &(inp->pipe.cmd);
	lists[1] = &(inp->hdoc_op.cmd);
	lists[2] = &(inp->app_op.cmd);
	lists[3] = &(inp->inp_op.cmd);
	lists[4] = &(inp->out_op.cmd);
}

static void	trim_spaces(t_data *inp)
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
		size = count_array_size(arr[i]);
		while (size > 0)
		{
			trimmed = ft_strtrim(arr[i][size - 1], " ");
			if (trimmed)
			{
				free(arr[i][size - 1]);
				arr[i][size - 1] = trimmed;
			}
			size--;
		}
	}
}

void	process_fds(t_data *inp)
{
	char	***lists[5];
	char	*del[4];
	char	**ptr;
	int		i;
	int		j;

	inp->input = ft_strdup(*inp->pipe.cmd);
	init_lists_and_del(inp, lists, del);
	i = -1;
	while (++i < 5)
	{
		ptr = *lists[i];
		while (ptr && *ptr)
		{
			j = -1;
			while (++j < 4)
				split_and_store(ptr, lists[j + 1], del[j]);
			ptr++;
		}
	}
	trim_spaces(inp);
	inp->command = ft_split(*inp->pipe.cmd, ' ');
}

// cc parsing.c utils/functions.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strdup.c utils/more_functions.c utils/even_more_functions.c ../include/libft/src/ft_strnstr.c ../include/libft/src/ft_strncmp.c -o parsing -g -Wall -Werror -Wextra