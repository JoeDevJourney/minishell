/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:43:54 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/08 16:38:17 by dchrysov         ###   ########.fr       */
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
