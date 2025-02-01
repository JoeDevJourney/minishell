/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_oper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 19:12:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int main()
// {
// 	char *res =	executable("mkfile");
// 	printf("Found in \'%s\'\n", res);
// }
// cc expansion_oper.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strncmp.c -Wall -Werror -Wextra
// int main()
// {
// 	char **arr;
// 	char **ptr;

// 	arr = malloc (5 * sizeof(char *));
// 	if (!arr)
// 		return (0);
// 	arr[0] = ft_strdup("ls");
// 	arr[1] = ft_strdup("-l");
// 	arr[2] = ft_strdup("$PWD1");
// 	arr[3] = ft_strdup("$USER");
// 	arr[4] = NULL;
// 	expansion_oper(arr);
// 	ptr = arr;
// 	while (*ptr)
// 		printf("\'%s\'\n", *ptr++);
// }

// cc expansion_oper.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_memmove.c ../include/libft/src/ft_strlen.c -o expansion_oper ../include/libft/src/ft_strdup.c -g -Wall -Werror -Wextra
