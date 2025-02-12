/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/12 17:45:37 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cleanup_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**copy_env(char **env)
{
	int		i;
	int		size;
	char	**env_copy;

	i = 0;
	size = 0;
	while (env[size])
		size++;
	env_copy = malloc((size + 1) * sizeof(char *));
	if (!env_copy)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	while (i < size)
	{
		env_copy[i] = strdup(env[i]);
		if (!env_copy[i])
			exit(EXIT_FAILURE);
		i++;
	}
	env_copy[size] = NULL;
	return (env_copy);
}

void	handle_escape(char **input, char **dst, bool sq, bool dq)
{
	if (!sq && (**input == '\\') && (*(*input + 1) == '"' \
		|| *(*input + 1) == '$' || *(*input + 1) == '\\' \
		|| *(*input + 1) == '`' || *(*input + 1) == '\n'))
	{
		(*input)++;
		*(*dst)++ = **input;
	}
}

void	update_quote_state(char c, bool *sq, bool *dq, bool escape)
{
	if (escape)
		return ;
	if (c == '\'' && !*dq)
		*sq = !*sq;
	else if (c == '"' && !*sq)
		*dq = !*dq;
}

void	add_command(char **arr, int *i, t_split_state *state)
{
	if (state->ptr > state->start)
	{
		arr[*i] = ft_strndub(state->start, state->ptr = state->start);
		(*i)++;
		state->start = state->ptr + 1;
	}
}
