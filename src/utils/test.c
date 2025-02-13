/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/13 20:54:36 by dchrysov         ###   ########.fr       */
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

static void	split_and_store(char **str, char ***rest, char *del)
{
	if (!str || !*str || !del)
		return ;
	char **split_arr = ft_split2(*str, del);
	if (!split_arr)
		return;
	free(*str);
	*str = ft_strdup(split_arr[0]);
	size_t new_count = count_array_size(split_arr) - 1;
	if (new_count > 0) {
		size_t old_count = count_array_size(*rest);
		size_t total_count = old_count + new_count;
		char **new_rest = malloc((total_count + 1) * sizeof(char *));
		if (!new_rest)
			return;
		size_t i = 0;
		while (i < old_count) {
			new_rest[i] = (*rest)[i];
			i++;
		}
		size_t j = 1;
		while (split_arr[j]) {
			new_rest[i++] = ft_strdup(split_arr[j++]);
		}
		new_rest[i] = NULL;
		free(*rest);
		*rest = new_rest;
	}
	size_t i = 0;
	while (split_arr[i]) {
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

void	parse_redirection(t_data *inp)
{
	char	**ptr;

	inp->inp_op.cmd = NULL;
	inp->app_op.cmd = NULL;
	inp->out_op.cmd = NULL;
	inp->hdoc_op.cmd = NULL;
	split_and_store(&inp->input, &inp->hdoc_op.cmd, "<<");
	split_and_store(&inp->input, &inp->app_op.cmd, ">>");
	split_and_store(&inp->input, &inp->inp_op.cmd, "<");
	split_and_store(&inp->input, &inp->out_op.cmd, ">");
	ptr = inp->hdoc_op.cmd;
	while (ptr && *ptr)
	{
		split_and_store(ptr, &inp->app_op.cmd, ">>");
		char **ptr1 = inp->app_op.cmd;
		while (ptr1 && *ptr1)
		{
			split_and_store(inp->app_op.cmd, &inp->inp_op.cmd, "<");
			char **ptr4 = inp->inp_op.cmd;
			while (ptr4 && *ptr4)
			{
				split_and_store(inp->inp_op.cmd, &inp->out_op.cmd, ">");
				ptr4++;
			}
			split_and_store(inp->app_op.cmd, &inp->out_op.cmd, ">");
			char **ptr5 = inp->out_op.cmd;
			while (ptr5 && *ptr5)
			{
				split_and_store(inp->out_op.cmd, &inp->inp_op.cmd, "<");
				ptr5++;
			}
			ptr1++;
		}
		split_and_store(ptr, &inp->inp_op.cmd, "<");
		char **ptr2 = inp->inp_op.cmd;
		while (ptr2 && *ptr2)
		{
			split_and_store(ptr2, &inp->app_op.cmd, ">>");
			char **ptr4 = inp->app_op.cmd;
			while (ptr4 && *ptr4)
			{
				split_and_store(ptr4, &inp->out_op.cmd, ">");
				ptr4++;
			}
			split_and_store(ptr2, &inp->out_op.cmd, ">");
			char **ptr5 = inp->out_op.cmd;
			while (ptr5 && *ptr5)
			{
				split_and_store(ptr5, &inp->app_op.cmd, ">>");
				ptr5++;
			}
			ptr2++;
		}
		split_and_store(ptr, &inp->out_op.cmd, ">");
		char **ptr3 = inp->out_op.cmd;
		while(ptr3 && *ptr3)
		{
			split_and_store(ptr3, &inp->inp_op.cmd, "<");
			char **ptr4 = inp->inp_op.cmd;
			while (ptr4 && *ptr4)
			{
				split_and_store(ptr4, &inp->app_op.cmd, ">>");
				ptr4++;
			}
			split_and_store(ptr3, &inp->app_op.cmd, ">>");
			char **ptr5 = inp->app_op.cmd;
			while (ptr5 && *ptr5)
			{
				split_and_store(ptr5, &inp->inp_op.cmd, "<");
				ptr5++;
			}
			ptr3++;
		}
		ptr++;
	}
}
int main()
{
	t_data inp;

	inp.input = ft_strdup("awk '{print $1}' > col1.txt < raw_data << heredoc4 >> append_results > final_result");
	parse_redirection(&inp);
	printf("'%s'\n", inp.input);
	printf("hdoc: [");
	while (inp.hdoc_op.cmd && *inp.hdoc_op.cmd)
		printf("'%s', ", *inp.hdoc_op.cmd++);
	printf("]\n");
	printf("inp: [");
	while (inp.inp_op.cmd && *inp.inp_op.cmd)
		printf("'%s', ", *inp.inp_op.cmd++);
	printf("]\n");
	printf("out: [");
	while (inp.out_op.cmd && *inp.out_op.cmd)
		printf("'%s', ", *inp.out_op.cmd++);
	printf("]\n");
	printf("app: [");
	while (inp.app_op.cmd && *inp.app_op.cmd)
		printf("'%s', ", *inp.app_op.cmd++);
	printf("]\n");
}

// cc test.c functions.c ../../include/libft/src/ft_strchr.c ../../include/libft/src/ft_strjoin.c ../../include/libft/src/ft_strlen.c ../../include/libft/src/ft_strlcat.c ../../include/libft/src/ft_strlcpy.c ../../include/libft/src/ft_strdup.c parsing.c more_functions.c ../../include/libft/src/ft_strnstr.c ../../include/libft/src/ft_strncmp.c -o test -g -Wall -Werror -Wextra