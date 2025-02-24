/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/20 18:56:27 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dupl_env(char ***arr, char **env)
{
	int	i;

	*arr = safe_malloc((count_array_size(env) + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
	{
		(*arr)[i] = ft_strdup(env[i]);
		if (!(*arr)[i])
		{
			while (i > 0)
				free((*arr)[--i]);
			free((*arr));
			*arr = NULL;
			return ;
		}
	}
	(*arr)[i] = NULL;
}

int	exec_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	exec_env(env);
// }

// cc env.c ../utils/functions.c ../utils/more_functions.c ../../include/libft/src/ft_strlen.c ../../include/libft/src/ft_strchr.c ../../include/libft/src/ft_strdup.c ../../include/libft/src/ft_strlcpy.c ../../include/libft/src/ft_strnstr.c ../../include/libft/src/ft_strncmp.c -o env -Wall -Werror -Wextra