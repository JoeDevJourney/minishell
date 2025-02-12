/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:36:03 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/12 17:55:02 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_quotes(const char *input)
{
	bool	sq;
	bool	dq;
	bool	escape;

	sq = false;
	dq = false;
	escape = false;
	while (*input)
	{
		if (!escape && *input == '\\' && (*(input + 1) == '"' || *(input \
			+ 1) == '`' || *(input + 1) == '$' || *(input + 1) == '\\' \
			|| *(input + 1) == '\n'))
		{
			escape = true;
			input++;
			continue ;
		}
		if (!escape && *input == '\'' && !dq)
			sq = !sq;
		if (!escape && *input == '"' && !sq)
			dq = !dq;
		escape = (*input == '\\' && !escape && dq);
		input++;
	}
	return (sq || dq);
}

char	*process_quotes(char *input)
{
	char	*res;
	char	*dst;
	bool	sq;
	bool	dq;
	bool	escape;

	res = malloc(ft_strlen(input) + 1);
	dst = res;
	sq = false;
	dq = false;
	escape = false;
	while (*input)
	{
		handle_escape(&input, &dst, sq, dq);
		update_quote_state(*input, &sq, &dq, escape);
		if (!((sq || dq) && (*input == '\'' || *input == '"')))
			*dst++ = *input;
		escape = (!sq && *input == '\\' && !escape && dq);
		input++;
	}
	*dst = '\0';
	return (res);
}

void	update_split_state(char c, t_split_state *state)
{
	if (state->escape)
	{
		state->escape = false;
		return ;
	}
	if (c == '\\' && !state->sq)
	{
		state->escape = true;
		return ;
	}
	if (c == '\'' && !state->dq)
		state->sq = !state->sq;
	if (c == '"' && !state->sq)
		state->dq = !state->dq;
}

char	**split_pipes(char *str)
{
	char			**arr;
	t_split_state	state;
	int				i;

	arr = malloc(64 * sizeof(char *));
	i = 0;
	init_split_state(&state, str);
	while (*state.ptr)
	{
		update_split_state(*state.ptr, &state);
		if (*state.ptr == '|' && !state.sq && !state.dq && !state.escape)
			add_command(arr, &i, &state);
		state.ptr++;
	}
	add_command(arr, &i, &state);
	arr[i] = NULL;
	return (arr);
}
