/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:52:59 by jbrandt           #+#    #+#             */
/*   Updated: 2024/10/29 11:35:07 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *store)
{
	char	buffer[BUFFER_SIZE + 1];
	int		reat;
	char	*tmp;

	reat = 1;
	while (reat > 0 && !ft_strchr(store, '\n'))
	{
		reat = read(fd, buffer, BUFFER_SIZE);
		if (reat < 0)
		{
			free(store);
			return (NULL);
		}
		buffer[reat] = '\0';
		tmp = store;
		store = str_join(store, buffer);
		if (!store)
		{
			free(tmp);
			return (NULL);
		}
	}
	return (store);
}

char	*ft_get_line(char *store)
{
	int		i;
	char	*res;
	int		j;

	i = 0;
	if (!store)
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\n')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (j < i)
	{
		res[j] = store[j];
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*update_store(char *store)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!store)
		return (NULL);
	while (store[i] && store[i] != '\n')
		i++;
	if (store[i] == '\0')
		return (free(store), NULL);
	res = malloc(sizeof(char) * (ft_strlen(store) - i + 1));
	if (!res)
		return (free(store), NULL);
	i++;
	while (store[i])
		res[j++] = store[i++];
	res[j] = '\0';
	free(store);
	return (res);
}

char	*get_next_line(int fd)
{
	static char		*store = NULL;
	char			*res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	store = ft_read(fd, store);
	if (!store)
		return (NULL);
	res = ft_get_line(store);
	if (!res || res[0] == '\0')
	{
		free(store);
		store = NULL;
		if (res)
			free(res);
		return (NULL);
	}
	store = update_store(store);
	return (res);
}

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *str = get_next_line(fd);
// 	printf("Line 1: %s\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("Line 1: %s\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("Line 1: %s\n", str);
// 	return (0);
// }
