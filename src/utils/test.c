/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/14 14:31:57 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_array_size(char **arr)
{
	size_t	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}

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
	inp->inp_op.cmd = NULL;
	inp->app_op.cmd = NULL;
	inp->out_op.cmd = NULL;
	inp->hdoc_op.cmd = NULL;
	lists[0] = &(inp->hdoc_op.cmd);
	lists[1] = &(inp->app_op.cmd);
	lists[2] = &(inp->inp_op.cmd);
	lists[3] = &(inp->out_op.cmd);
}

void	parse_redirection(t_data *inp)
{
	char	***lists[4];
	char	*del[4];
	char	**ptr;
	int		i;
	int		j;

	init_lists_and_del(inp, lists, del);
	i = -1;
	while (++i < 4)
		split_and_store(&inp->input, lists[i], del[i]);
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
}

// int main()
// {
// 	t_data inp;

// 	inp.input = ft_strdup("cat << hdoc1 < infile1 > outfile1 << hdoc2 >> append1 < infile2");
// 	parse_redirection(&inp);
// 	printf("'%s'\n", inp.input);
// 	printf("hdoc: [");
// 	while (inp.hdoc_op.cmd && *inp.hdoc_op.cmd)
// 		printf("'%s', ", *inp.hdoc_op.cmd++);
// 	printf("]\n");
// 	printf("inp: [");
// 	while (inp.inp_op.cmd && *inp.inp_op.cmd)
// 		printf("'%s', ", *inp.inp_op.cmd++);
// 	printf("]\n");
// 	printf("out: [");
// 	while (inp.out_op.cmd && *inp.out_op.cmd)
// 		printf("'%s', ", *inp.out_op.cmd++);
// 	printf("]\n");
// 	printf("app: [");
// 	while (inp.app_op.cmd && *inp.app_op.cmd)
// 		printf("'%s', ", *inp.app_op.cmd++);
// 	printf("]\n");
// }

// cc test.c functions.c ../../include/libft/src/ft_strchr.c ../../include/libft/src/ft_strjoin.c ../../include/libft/src/ft_strlen.c ../../include/libft/src/ft_strlcat.c ../../include/libft/src/ft_strlcpy.c ../../include/libft/src/ft_strdup.c parsing.c more_functions.c ../../include/libft/src/ft_strnstr.c ../../include/libft/src/ft_strncmp.c -o test -g -Wall -Werror -Wextra