/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/25 19:04:01 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	if (len == 0 || *src == '\0')
	{
		if (len > 0)
			*dst = '\0';
		return (dst);
	}
	else
	{
		*dst = *src;
		ft_strncpy(dst + 1, src + 1, len - 1);
	}
	return (dst);
}

void	add_command(t_list **list, const char *start, const char *end)
{
	t_list	*new_cmd;
	size_t	len;
	t_list	*temp;

	new_cmd = malloc(sizeof(t_list));
	len = end - start;
	new_cmd->str = malloc(len + 1);
	ft_strncpy(new_cmd->str, start, len);
	new_cmd->str[len] = '\0';
	new_cmd->next = NULL;
	if (*list == NULL)
		*list = new_cmd;
	else
	{
		temp = *list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

static char	*join_cmd(char **arr)
{
	char	*res;
	char	*with_space;
	int		i;

	i = 0;
	res = ft_strdup(arr[i]);
	while (arr[++i])
	{
		with_space = ft_strjoin(res, " ");
		free(res);
		res = ft_strjoin(with_space, arr[i]);
		free(with_space);
	}
	return (res);
}

void	expansion_oper(char **env, char **cmd)
{
	char	**res;
	char	**arr;
	int		i;

	arr = ft_split(*cmd, ' ');
	res = safe_malloc((count_array_size(arr) + 1) * sizeof(char *));
	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] == '$' && get_env_val(env, arr[i] + 1))
			res[i] = ft_strdup(get_env_val(env, arr[i] + 1));
		else
			res[i] = ft_strdup(arr[i]);
	}
	res[i] = NULL;
	free(*cmd);
	*cmd = join_cmd(res);
	free_array(arr);
	free_array(res);
}

// int main(int argc, char **argv, char **env)
// {
// 	char *str = ft_strdup("Hello $PWD malaka!");

// 	(void)argc;
// 	(void)argv;
// 	printf("\nbefore: '%s'\n", str);
// 	expansion_oper(env, &str);
// 	printf("after: '%s'\n\n", str);
// 	free(str);
// }

// cc *.c ../builtins/cd/cd_utils.c ../../include/libft/src/*.c -o quote_utils -Wall -Werror -Wextra -g -lreadline