/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/07 18:22:29 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_export(t_data *inp)
{
	char	*name;
	char	*value;
	int		res;
	int		i;

	i = 0;
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
