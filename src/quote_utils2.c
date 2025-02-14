/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:59:52 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/14 15:42:48 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strndub(const char *s, size_t n)
{
	char	*result;
	size_t	len;

	len = ft_strnlen(s, n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	return ((char *)ft_memcpy(result, s, len));
}

void	init_split_state(t_split_state *state, char *str)
{
	state->sq = false;
	state->dq = false;
	state->escape = false;
	state->start = str;
	state->ptr = str;
}

void	add_node(t_list **head, const char *str)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	new_node->str = ft_strdup(str);
	if (!new_node->str)
	{
		perror("strdup error");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_memmove(ptr, s, (size_t)ft_strlen(s) + 1);
	return (ptr);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*d;
	const unsigned char		*s;
	size_t					i;

	i = 0;
	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i < len)
	{
		if (d < s)
		{
			d[i] = s[i];
			i++;
		}
		else
		{
			d[len - i - 1] = s[len - i - 1];
			i ++;
		}
	}
	return (dst);
}
