/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:45:37 by jbrandt           #+#    #+#             */
/*   Updated: 2024/10/29 11:41:56 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_strlen(const char *str);
char	*str_join(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
void	*ft_memcpy(void *dst, void *src, size_t n);
char	*ft_read(int fd, char *store);
char	*ft_get_line(char *store);
char	*update_store(char *store);
char	*get_next_line(int fd);

#endif