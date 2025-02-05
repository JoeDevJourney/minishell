/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/05 12:37:08 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	is_valid_env_name(const char *name)
// {
// 	int	i;

// 	if (!name || !*name || (ft_isdigit(*name) && *name != '_'))
// 		return (0);
// 	i = 0;
// 	while (name[i] && name[i] != '=')
// 	{
// 		if (!ft_isalnum(name[i]) && name[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static void	print_sorted_env(char **env)
// {
// 	char	**copy;
// 	int		i;
// 	int		size;

// 	size = 0;
// 	while (env[size])
// 		size++;
// 	copy = malloc((size + 1) * sizeof(char *));
// 	if (!copy)
// 		return (perror("malloc error"));
// 	i = -1;
	
// }
