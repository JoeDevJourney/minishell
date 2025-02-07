/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/05 17:54:50 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_env_name(const char *name)
{
	int	i;

	if (!name || !*name || (ft_isdigit(*name) && *name != '_'))
		return (0);
	i = 0;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
	{
		if (isalnum(*str) && *str != '_')
			return (0);
	}
	return (1);
}

static void	print_sorted_env(char **env)
{
	char	**copy;
	int		i;
	int		size;

	size = 0;
	while (env[size])
		size++;
	copy = malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (perror("malloc error"));
	i = -1;
	while (++i < size)
		copy[i] = env[i];
	copy[size] = NULL;
	i = -1;
	while (++i < size)
	{
		if (ft_strcmp(copy[i], copy[i + 1]) > 0 && (copy[i + 1]))
			ft_swap(&copy[i], &copy[i + 1], sizeof(char *));
	}
	i = -1;
	while (copy[++i])
		printf("declare -x %s\n", copy[i]);
	free(copy);
}

int	process_export_argument(char **env, char *arg)
{
	char	*name;
	char	*value;

	value = ft_strchr(arg, '=');
	if (value)
	{
		name = ft_substr(arg, 0, value - arg);
		value++;
	}
	else
	{
		name = ft_strdup(arg);
		value = "";
	}
	if (update_env_var(env, name, value) != 0)
	{
		free(name);
		return (1);
	}
	free(name);
	return (0);
}

int	ft_export(char **env, char **args)
{
	int	i;

	i = 1;
	if (!args[1])
		return (print_sorted_env(env), 0);
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			return (ft_write_error("export error"), 1);
		if (process_export_argument(env, args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
