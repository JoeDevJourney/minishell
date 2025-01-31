/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_oper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 18:53:02 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Searches the **arr for a $ to replace the environmental key
 * with its corresponding value
 */
// void	expansion_oper(char **arr)
// {
// 	char	**ptr;
// 	char	*val;

// 	ptr = arr;
// 	while (*ptr)
// 	{
// 		if (ft_strchr(*ptr, '$'))
// 		{
// 			val = getenv(ft_strchr(*ptr, '$') + 1);
// 			free(*ptr);
// 			if (val)
// 				*ptr = ft_strdup(val);
// 			else
// 				*ptr = NULL;
// 		}
// 		ptr++;
// 	}
// }

static char	*executable(char *name)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**path;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
	{
		printf("$PATH not set\n");
		return (NULL);
	}
	while (*path)
	{
		dir = opendir(*path);
		if (!dir)
			perror("opendir");
		else
		{
			entry = readdir(dir);
			while (entry)
			{
				if (entry && !ft_strncmp(name, entry->d_name, ft_strlen(name)))
					return (*path);
				entry = readdir(dir);
			}
			closedir(dir);
		}
		path++;
	}
	return (NULL);
	// free
}

int main()
{
	char *res =	executable("mkfile");
	printf("Found in \'%s\'\n", res);
}
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
