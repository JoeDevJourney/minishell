/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guess_what_more_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/09 12:20:38 by dchrysov         ###   ########.fr       */
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
	while ((*str)[++i])
		if ((*str)[i] == '\'' && !open_dq)
			open_sq = !open_sq;
	if (open_sq)
		ask_for_quote(str, '\'');
	i = -1;
	while ((*str)[++i])
		if ((*str)[i] == '"' && !open_sq)
			open_dq = !open_dq;
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
char	*get_env_val(t_data inp, char *name)
{
	size_t	name_len;
	int		i;

	name_len = ft_strlen(name);
	i = -1;
	if (!ft_strncmp(name, "$", 1) && name_len == 1)
		return (ft_itoa(inp.pid));
	if (!ft_strncmp(name, "\?", 1) && name_len == 1)
		return (ft_itoa(inp.ret_val));
	while (inp.env[++i])
		if (!ft_strncmp(inp.env[i], name, name_len)
			&& inp.env[i][name_len] == '=')
			return (&inp.env[i][name_len + 1]);
	return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
