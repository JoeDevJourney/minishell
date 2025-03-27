/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guess_what_more_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/27 15:19:40 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			return (free(rem));
		free(rem);
	}
}

void	check_open_quotes(char **str)
{
	int		i;
	bool	open_sq;
	bool	open_dq;

	open_sq = false;
	open_dq = false;
	i = -1;
	while (str && (*str)[++i])
	{
		if ((*str)[i] == '\'' && !open_dq)
			open_sq = !open_sq;
		if ((*str)[i] == '"' && !open_sq)
			open_dq = !open_dq;
	}
	if (open_sq)
		ask_for_quote(str, '\'');
	if (open_dq)
		ask_for_quote(str, '"');
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

/**
 * @brief Extracts the env variable from the env list.
 */
char	*get_env_val(t_data inp, char *input)
{
	t_env	*current;

	current = inp.env;
	if (!ft_strncmp(input, "?", 1) && ft_strlen(input) == 1)
		return (ft_itoa(inp.ret_val));
	if (!ft_strncmp(input, "$", 1) && ft_strlen(input) == 1)
		return (ft_itoa(inp.pid));
	while (current)
	{
		if (!ft_strncmp(current->name, input, ft_strlen(input))
			&& ft_strlen(input) == ft_strlen(current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !*s1)
		result = ft_strjoin("", s2);
	if (!s2 || !*s2)
		result = ft_strjoin(s1, "");
	else
		result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
