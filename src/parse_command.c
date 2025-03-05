/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:56:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/05 20:14:59 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Counts words when not included in quotes 
 */
static int	count_tokens(char *str)
{
	bool	open_sq;
	bool	open_dq;
	int		num;

	open_sq = false;
	open_dq = false;
	num = 1;
	while (*str)
	{
		if (*str == '"' && !open_sq)
			open_dq = !open_dq;
		if (*str == '\'' && !open_dq)
			open_sq = !open_sq;
		if (*str == ' ' && !open_dq && !open_sq)
		{
			num++;
			while (*str && *str == ' ')
				str++;
			continue ;
		}
		str++;
	}
	return (num);
}

/**
 * @brief It uses ' ' or '\0' to extract the quoted substring, quotes removed,
 * from str and saves it as an individual token to the arr.
 */
static void	quoted_token(char **str, char **arr, int *i)
{
	int		len;
	int		copy_i;
	bool	open_sq;
	bool	open_dq;

	len = 0;
	open_sq = false;
	open_dq = false;
	copy_i = *i - 1;
	while ((*str)[*i] && (!((*str)[*i] == ' ' && !open_sq && !open_dq)))
	{
		if ((*str)[*i] == '"' && !open_sq)
			open_dq = !open_dq;
		else if ((*str)[*i] == '\'' && !open_dq)
			open_sq = !open_sq;
		else
			len++;
		(*i)++;
	}
	*arr = safe_malloc(len + 1);
	len = 0;
	while (++copy_i < *i)
		if ((*str)[copy_i] != '"' && (*str)[copy_i] != '\'')
			(*arr)[len++] = (*str)[copy_i];
	(*arr)[len] = '\0';
}

/**
 * @brief It uses ' ' or '\0' to extract the unquoted substring and save it
 * to the arr.
 */
static void	unquoted_token(char **str, char **arr, int *i)
{
	int	len;

	len = *i;
	while (1)
	{
		if ((*str)[len] == ' ' || (*str)[len] == '\0')
			break ;
		len++;
	}
	len -= *i;
	*arr = safe_malloc(len + 1);
	ft_strlcpy(*arr, *str + *i, len + 1);
	(*i) += len;
}

/**
 * @brief It breaks the str into tokens, according to quote type,
 * as well as removing the quotes themselves.
 */
static void	tokenization(char **str, char ***arr)
{
	int	i;
	int	word_i;

	i = -1;
	word_i = -1;
	*arr = safe_malloc((count_tokens(*str) + 1) * sizeof(char *));
	while ((*str)[++i])
	{
		while ((*str)[i] == ' ')
			i++;
		if ((*str)[i] == '"' || (*str)[i] == '\'')
			quoted_token(str, &(*arr)[++word_i], &i);
		else
			unquoted_token(str, &(*arr)[++word_i], &i);
		if ((*str)[i] == '\0')
			break ;
	}
	(*arr)[++word_i] = NULL;
}

void	parse_command(t_data *inp)
{
	// check open quotes
	inp->cmd = ft_strdup(*inp->pipe.cmd);
	parse_redir(inp);
	expansion(&inp->cmd, inp->env);
	tokenization(&inp->cmd, &inp->tok);
	// print_data(*inp);
}
