/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 14:50:31 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	sort_env_copy(char **copy, int size)
// {
// 	int	i;
// 	int	swapped;

// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		i = -1;
// 		while (++i < size - 1)
// 		{
// 			if (ft_strcmp(copy[i], copy[i + 1]) > 0)
// 			{
// 				ft_swap(&copy[i], &copy[i + 1], sizeof(char *));
// 				swapped = 1;
// 			}
// 		}
// 	}
// }

// static void	print_env_copy(char **copy)
// {
// 	int		i;
// 	char	*value;

// 	i = -1;
// 	while (copy[++i])
// 	{
// 		printf("declare -x ");
// 		value = ft_strchr(copy[i], '=');
// 		if (value)
// 		{
// 			printf("%.*s\"", (int)(value - copy[i] + 1), copy[i]);
// 			value++;
// 			printf("%s\"", value);
// 		}
// 		else
// 			printf("%s", copy[i]);
// 		printf("\n");
// 	}
// }

// static void	print_sorted_env(char **env)
// {
// 	char	**copy;
// 	int		size;

// 	size = 0;
// 	while (env[size])
// 		size++;
// 	copy = ft_arrdup(env, size + 1);
// 	if (!copy)
// 		return (perror("malloc error"));
// 	sort_env_copy(copy, size);
// 	print_env_copy(copy);
// 	ft_arrfree(copy);
// }

/**
 * @brief Creates/updates the env variable arg with the new value
 * 
 * @param value The new value
 */
static void	handle_export_arg(char **arg, char ***env)
{
	char	*name;
	char	*value;
	int		i;

	i = -1;
	while (arg[++i])
	{
		value = ft_strchr(*arg, '=');
		if (value)
		{
			name = ft_substr(*arg, 0, value - *arg);
			value++;
		}
		else
		{
			name = ft_strdup(*arg);
			value = NULL;
		}
		update_env_var(env, name, value);
		free(name);
		printf("%d\n", i);
	}
}

int	ft_export(char **cmd, char ***env)
{
	handle_export_arg(&cmd[1], env);
	return (0);
}
