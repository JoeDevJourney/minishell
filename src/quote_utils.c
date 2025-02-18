/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/18 17:10:06 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->str);
		free(tmp);
	}
}

void	add_command(t_list **list, const char *start, const char *end)
{
	t_list	*new_cmd;
	size_t	len;
	t_list	*temp;

	new_cmd = malloc(sizeof(t_list));
	len = end - start;
	new_cmd->str = malloc(len + 1);
	ft_strncpy(new_cmd->str, start, len);
	new_cmd->str[len] = '\0';
	new_cmd->next = NULL;
	if (*list == NULL)
		*list = new_cmd;
	else
	{
		temp = list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

t_quote_state	init_quote_state(void)
{
	t_quote_state	state;

	state.sq = false;
	state.dq = false;
	state.escape = false;
	return (state);
}

unsigned long	ft_strlen(const char str[])
{
	const char		*ptr;
	unsigned long	len;

	if (!str)
		return (0);
	ptr = str;
	len = 0;
	while (*ptr)
	{
		len++;
		ptr++;
	}
	return (len);
}
