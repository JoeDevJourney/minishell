/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:26:25 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/25 19:48:24 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int	count_tokens(const char *str)
{
	int		count;
	bool	in_quotes;
	char	quote_char;

	count = 0;
	in_quotes = false;
	quote_char = 0;
	while (str && *str)
	{
		while (is_whitespace(*str))
			str++;
		if (*str == '\0')
			break ;
		count++;
		while (*str && (in_quotes || !is_whitespace(*str)))
		{
			if (*str == '"' || *str == '\'')
			{
				if (!in_quotes)
				{
					in_quotes = true;
					quote_char = *str;
				}
				else if (quote_char == *str)
					in_quotes = false;
			}
			str++;
		}
	}
	return (count);
}

static char	*extract_token(const char **str)
{
	char	buffer[1024];
	int		i;
	bool	in_quotes;
	char	quote_char;

	i = 0;
	in_quotes = false;
	quote_char = 0;
	while (is_whitespace(**str))
		(*str)++;
	while (**str && (in_quotes || !is_whitespace(**str)))
	{
		if (**str == '"' || **str == '\'')
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote_char = **str;
			}
			else if (quote_char == **str)
				in_quotes = false;
			else
				buffer[i++] = **str;
		}
		(*str)++;
	}
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}

char	**ft_split_preserve_quotes(const char *str)
{
	int		token_count;
	char	**result;
	int		i;

	token_count = count_tokens(str);
	result = malloc((token_count + 1) * sizeof(char *));
	i = 0;
	if (!result)
		return (NULL);
	while (i < token_count)
		result[i++] = extract_token(&str);
	result[i] = NULL;
	return (result);
}
