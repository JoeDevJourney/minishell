/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/04 18:53:46 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_env_name(const char *name)
{
	if (!name || !(*name == '_' || ft_isalpha(*name)))
		return (0);
	while (*name && *name != '=')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

static void	print_exported_vars(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

int	ft_export(char **env, char **args)
{
	int		status;
	char	*arg;
	char	*name;
	int		i;

	status = 0;
	if (args[1])
		return (print_exported_vars(env), 0);
	i = 1;
	while ((arg = args[i++]))
	{
		name = ft_substr(arg, 0, ft_strchr(arg, '='))
	}
}
