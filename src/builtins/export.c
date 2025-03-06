/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 17:44:33 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Creates/updates the env variable arg with the new value
 * 
 * @param value The new value
 */
static int	handle_export_arg(char **arg, char ***env)
{
	char	*name;
	char	*value;
	int		res;
	int		i;

	i = 0;
	while (arg[++i])
	{
		value = ft_strchr(arg[i], '=');
		if (value)
		{
			name = ft_substr(arg[i], 0, value - arg[i]);
			value++;
		}
		else
		{
			name = ft_strdup(arg[i]);
			value = NULL;
		}
		res = update_env_var(env, name, value);
		free(name);
	}
	return (res);
}

int	exec_export(t_data *inp)
{
	return (handle_export_arg(inp->tok, &inp->env));
}
