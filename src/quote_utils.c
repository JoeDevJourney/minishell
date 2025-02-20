/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/19 14:26:48 by jbrandt          ###   ########.fr       */
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

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	if (len == 0 || *src == '\0')
	{
		if (len > 0)
			*dst = '\0';
		return (dst);
	}
	else
	{
		*dst = *src;
		ft_strncpy(dst + 1, src + 1, len - 1);
	}
	return (dst);
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
		temp = *list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

t_quote_state	init_quote_state(void)
{
	return ((t_quote_state){false, false, false});
}

unsigned long	ft_strlen(const char str[])
{
	unsigned long	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
