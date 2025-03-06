/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:56:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/06 10:45:23 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Tokens are everything in betweem two whotespaces. 
 * Spaces inside quotes don't count.  
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
static void	extract_token(char **str, char **arr, int *i)
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
 * @brief It breaks the str into tokens, removing the quotes if encountered.
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
		extract_token(str, &(*arr)[++word_i], &i);
		if ((*str)[i] == '\0')
			break ;
	}
	(*arr)[++word_i] = NULL;
}

void	parse_command(t_data *inp)
{
	check_open_quotes(inp->pipe.cmd);
	inp->cmd = ft_strdup(*inp->pipe.cmd);
	parse_redir(inp);
	expansion(&inp->cmd, *inp);
	tokenization(&inp->cmd, &inp->tok);
}
