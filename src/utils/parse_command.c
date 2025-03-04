/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:56:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/04 14:58:55 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Counts words when not included in quotes 
 */
static int	count_tokens(char *str)
{
	bool	closed_q;
	int		res;

	closed_q = true;
	res = 0;
	while (*str)
	{
		if (*str == ' ' && closed_q)
			res++;
		else if (*str == '"' || *str == '\'')
			closed_q = !closed_q;
		str++;
	}
	return (res + 1);
}

/**
 * @brief It uses ' ' or '\0' to extract the quoted substring, quotes including,
 * from str and saves it as an individual token to the arr.
 */
static void	quoted_token(char **str, char **arr, int *i)
{
	char	quote;
	int		len;

	len = 1;
	quote = *(*str + *i);
	while ((*str)[++*i])
	{
		len++;
		if ((*str)[*i] == quote &&
			((*str)[*i + 1] == ' ' || (*str)[*i + 1] == '\0'))
			break ;
	}
	*arr = safe_malloc(len + 1);
	ft_strlcpy(*arr, *str + *i - len + 1, len + 1);
}

/**
 * @brief It uses ' ' or '\0' to extract the unquoted substring and save it
 * to the arr.
 */
static void	unquoted_token(char **str, char **arr, int *i)
{
	int	len;

	len = 0;
	while (1)
	{
		if ((*str)[*i] == ' ' || (*str)[*i] == '\0')
			break ;
		len++;
		(*i)++;
	}
	*arr = safe_malloc(len + 1);
	ft_strlcpy(*arr, *str + *i - len, len + 1);
}

void	parse_command(t_data *inp)
{
	int		word_i;
	int		i;

	inp->command = safe_malloc((count_tokens(inp->pipe.cmd[0]) + 1)
			* sizeof(char *));
	word_i = -1;
	i = -1;
	while (inp->pipe.cmd[0][++i])
	{
		while (inp->pipe.cmd[0][i] == ' ')
			i++;
		if (inp->pipe.cmd[0][i] == '"' || inp->pipe.cmd[0][i] == '\'')
			quoted_token(&inp->pipe.cmd[0], &inp->command[++word_i], &i);
		else
			unquoted_token(&inp->pipe.cmd[0], &inp->command[++word_i], &i);
		if (inp->pipe.cmd[0][i] == '\0')
			break ;
	}
	inp->command[++word_i] = NULL;
}
