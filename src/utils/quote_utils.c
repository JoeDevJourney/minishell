/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/24 19:23:31 by dchrysov         ###   ########.fr       */
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
	char	*temp;
	char	*res;
	char	*with_space;

	if (!arr || !*arr)
		return (NULL);
	temp = NULL;
	temp = ft_strdup(*arr++);
	while (*arr)
	{
		with_space = ft_strjoin(temp, " ");
		free(temp);
		res = ft_strjoin(with_space, *arr);
		free(with_space);
		temp = res;
		arr++;
	}
	return (free(temp), res);
}

void	expansion_oper(char **env, char **cmd)
{
	char	**arr;
	char	*val;
	int		i;

	arr = ft_split(*cmd, ' ');
	i = -1;
	while (arr[++i])
	{
		if (arr[i][0] == '$')
		{
			val = ft_strdup(arr[i] + 1);
			free(arr[i]);
			arr[i] = get_env_val(env, val);
			free(val);
		}
	}
	if (val)
	{
		free(*cmd);
		*cmd = join_cmd(arr);
	}
	// free_array(arr);
}

int main(int argc, char **argv, char **env)
{
	char *str = ft_strdup("Hello $SHLVL malaka!");

	(void)argc;
	(void)argv;
	expansion_oper(env, &str);
	printf("res: '%s'\n", str);
	// free(str);
}