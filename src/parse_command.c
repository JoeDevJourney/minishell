/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:56:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/29 20:03:59 by jbrandt          ###   ########.fr       */
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
 * @brief Copies the content of the the quoted string passed as input to the tok
 * 
 * @param start is the starting index of the string
 * @param end is the ending index of the string
 */
static void	copy_to_token(char *str, char *tok, int start, int end)
{
	bool	open_sq;
	bool	open_dq;
	int		j;

	open_sq = false;
	open_dq = false;
	j = 0;
	while (++start < end)
	{
		if ((!open_sq && str[start] == '"') || (!open_dq && str[start] == '\''))
		{
			if (!open_sq && str[start] == '"')
				open_dq = !open_dq;
			else
				open_sq = !open_sq;
			continue ;
		}
		if (open_dq && str[start] == '\\' && (str[start + 1] == '"'
				|| str[start + 1] == '$' || str[start + 1] == '\\'))
			start++;
		else if (!open_sq && !open_dq && str[start] == '\\' && str[start + 1])
			start++;
		tok[j++] = str[start];
	}
	tok[j] = '\0';
}

/**
 * @brief It uses ' ' or '\0' to extract the quoted substring, quotes removed,
 * from str and saves it as an individual tempen to the arr.
 * 
 * @param i index that stops at the first ' ' that's not included in quotes 
 * @param len length of the extracted token.
 * 
 * @note i and len don't always match
 */
static void	extract_token(char **str, char **arr, int *i)
{
	int		len;
	int		start;
	bool	open_sq;
	bool	open_dq;

	len = 0;
	open_sq = false;
	open_dq = false;
	start = *i - 1;
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
	copy_to_token(*str, *arr, start, *i);
}

/**
 * @brief It breaks the str into tokens, removing the quotes if encountered.
 * 
 * @param str the address of the string to be scanned.
 * @param arr the address of the arr of strings for the tokens to be saved.
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

bool	parse_input(t_data *inp)
{
	check_open_quotes(inp->pipe.cmd);
	if (inp->pipe.cmd && *inp->pipe.cmd)
	{
		// inp->cmd = ft_strdup(*inp->pipe.cmd);
		if (!parse_redir(inp))
			return (false);
		expand_redir(inp);
		expansion(&inp->cmd, *inp);
		tokenization(&inp->cmd, &inp->tok);
	}
	return (true);
}
