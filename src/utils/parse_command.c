/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:56:36 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/04 20:00:06 by dchrysov         ###   ########.fr       */
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
static void	quoted_token(char **str, char **arr, char **env, int *i)
{
	int		len;
	bool	open_sq;
	bool	open_dq;

	len = 0;
	open_sq = false;
	open_dq = false;
	printf("%s\n", *str); pause();
	while (1)
	{
		if ((*str)[*i] == '"' && !open_sq)
			open_dq = !open_dq;
		if ((*str)[*i] == '\'' && !open_dq)
			open_sq = !open_sq;
		if (((*str)[*i] == ' ' && !open_dq && !open_sq) || (*str)[*i] == '\0')
			break ;
		(*i)++;
		len++;
	}
	*arr = safe_malloc(len + 1);
	ft_strlcpy(*arr, *str + *i - len, len + 1);
	expnd_quotes(arr, &env, NULL);
}

/**
 * @brief It uses ' ' or '\0' to extract the unquoted substring and save it
 * to the arr.
 */
static void	unquoted_token(char **str, char **arr, char **env, int *i)
{
	int	len;

	len = 0;
	while (1)
	{
		if ((*str)[*i] == ' ' || (*str)[*i] == '\0')
			break ;
		(*i)++;
		len++;
	}
	*arr = safe_malloc(len + 1);
	ft_strlcpy(*arr, *str + *i - len, len + 1);
	expnd_quotes(arr, &env, NULL);
}

void	parse_command(t_data *inp)
{
	int		word_i;
	int		i;

	inp->command = safe_malloc((count_tokens(inp->input) + 1)
			* sizeof(char *));
	word_i = -1;
	i = -1;
	while (inp->input[++i])
	{
		while (inp->input[i] == ' ')
			i++;
		if (inp->input[i] == '"' || inp->input[i] == '\'')
			quoted_token(&inp->input, &inp->command[++word_i], inp->env, &i);
		else
			unquoted_token(&inp->input, &inp->command[++word_i], inp->env, &i);
		if (inp->input[i] == '\0')
			break ;
	}
	inp->command[++word_i] = NULL;
}
