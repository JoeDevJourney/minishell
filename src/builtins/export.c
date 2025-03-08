/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/08 15:16:37 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	sort_env_copy(char **copy, int size)
// {
// 	int	i;
// 	int	swapped;
//
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

static int	print_env_copy(char **copy)
{
	int		i;
	char	*value;

	i = -1;
	while (copy[++i])
	{
		printf("declare -x ");
		value = ft_strchr(copy[i], '=');
		if (value)
		{
			printf("%.*s\"", (int)(value - copy[i] + 1), copy[i]);
			value++;
			printf("%s\"", value);
		}
		else
			printf("%s", copy[i]);
		printf("\n");
	}
	return (0);
}

// static void	print_sorted_env(char **env)
// {
// 	char	**copy;
// 	int		size;
//
// 	size = 0;
// 	while (env[size])
// 		size++;
// 	copy = ft_arrdup(env, size + 1);
// 	if (!copy)
// 		return (perror("malloc error"));
// 	// sort_env_copy(copy, size);
// 	print_env_copy(copy);
// 	ft_arrfree(copy);
// }

int	exec_export(t_data *inp)
{
	char	*name;
	char	*value;
	int		res;
	int		i;

	i = 0;
	if (count_array_size(inp->tok) == 1)
		return (print_env_copy(inp->env));
	while (inp->tok[++i])
	{
		value = ft_strchr(inp->tok[i], '=');
		if (value)
		{
			name = ft_substr(inp->tok[i], 0, value - inp->tok[i]);
			value++;
		}
		else
		{
			name = ft_strdup(inp->tok[i]);
			value = NULL;
		}
		res = update_env_var(&inp->env, name, value);
		free(name);
	}
	return (res);
}
