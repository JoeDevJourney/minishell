/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/27 13:56:48 by dchrysov         ###   ########.fr       */
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

/**
 * @brief Merges the strings of an arr back together, separated by the del
 */
char	*join_cmd(char **arr, char *del)
{
	char	*res;
	char	*with_space;
	int		i;

	i = 0;
	res = ft_strdup(arr[i]);
	while (arr[++i])
	{
		with_space = ft_strjoin(res, del);
		free(res);
		res = ft_strjoin(with_space, arr[i]);
		free(with_space);
	}
	return (res);
}

static void	ask_for_quote(char **str, char quote)
{
	char	*temp;
	char	*rem;

	while (1)
	{
		temp = ft_strjoin(*str, "\n");
		rem = readline("> ");
		free(*str);
		*str = ft_strjoin(temp, rem);
		free(temp);
		if (ft_strchr(rem, quote))
		{
			free(rem);
			break ;
		}
		free(rem);
	}
}

void	check_open_quotes(char **str, char quote)
{
	int		i;
	int		num;

	i = -1;
	num = 0;
	while ((*str)[++i])
		if ((*str)[i] == quote)
			num++;
	if (num % 2 != 0)
		ask_for_quote(str, quote);
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