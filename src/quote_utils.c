/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/14 12:31:08 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list(t_list *head)
{
	t_list	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->str);
		free(temp);
	}
}

t_list	*copy_env_list(char **env)
{
	t_list	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		add_node(&env_list, env[i]);
		i++;
	}
	return (env_list);
}

// void	handle_escape(char **input, char **dst, bool sq)
// {
// 	if (!sq && (**input == '\\') && (*(*input + 1) == '"' \
// 		|| *(*input + 1) == '$' || *(*input + 1) == '\\' \
// 		|| *(*input + 1) == '`' || *(*input + 1) == '\n'))
// 	{
// 		(*input)++;
// 		*(*dst)++ = **input;
// 	}
// }

// void	update_quote_state(char c, bool *sq, bool *dq, bool escape)
// {
// 	if (escape)
// 		return ;
// 	if (c == '\'' && !*dq)
// 		*sq = !*sq;
// 	else if (c == '"' && !*sq)
// 		*dq = !*dq;
// }

void	add_command(t_list **list, t_split_state *state)
{
	char	*command;

	if (state->ptr > state->start)
	{
		command = ft_strndub(state->start, state->ptr - state->start);
		add_node(list, command);
		free(command);
		state->start = state->ptr + 1;
	}
}
