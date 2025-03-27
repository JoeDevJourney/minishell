/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/27 17:58:56 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_env_copy(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		printf("declare -x %s", current->name);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
	return (0);
}

int	exec_export(t_data *inp)
{
	char	*name;
	char	*value;
	int		i;

	if (count_array_size(inp->tok) == 1)
		return (print_env_copy(inp->env));
	i = 0;
	while (inp->tok[++i])
	{
		name = ft_strdup(inp->tok[i]);
		value = ft_strchr(name, '=');
		if (value)
		{
			*(value)++ = '\0';
			if (*name == '\0')
				return (printf("bash: %s: `%s': Not a valid identifier\n",
						*inp->tok, inp->tok[i]), 1);
			if (update_env_var(&inp->env, name, value) != 0)
				return (perror(inp->tok[i]), errno);
		}
		free(name);
	}
	return (0);
}
