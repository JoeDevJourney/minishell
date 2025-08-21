/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:56:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/30 20:02:16 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Counts the number of tokens in a string, ignoring spaces inside quotes.
 * 
 * @param str Input string.
 * @return int Number of tokens.
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
 * @brief Copies the content of a quoted string to a token, removing quotes.
 * 
 * @param str Input string.
 * @param tok Output token buffer.
 * @param start Starting index.
 * @param end Ending index.
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
 * @brief Extracts a token from the input string, handling quotes.
 * 
 * @param str Pointer to input string.
 * @param arr Pointer to output token array.
 * @param i Pointer to current index in input string.
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
 * @brief Tokenizes the input string into an array, removing quotes.
 * 
 * @param str Pointer to input string.
 * @param arr Pointer to output array of tokens.
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

/**
 * @brief Parses the input command, handling redirections and expansions.
 * 
 * @param inp Pointer to main data structure.
 * @return true if parsing succeeded, false otherwise.
 */
bool	parse_input(t_data *inp)
{
	check_open_quotes(inp->pipe.cmd);
	if (inp->pipe.cmd && *inp->pipe.cmd)
	{
		parse_redir(inp);
		if (!expand_redir(inp))
			return (false);
		expansion(&inp->cmd, *inp);
		tokenization(&inp->cmd, &inp->tok);
	}
	return (true);
}
