/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:58:38 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/25 19:06:02 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sort_env_copy(char **copy, int size)
{
	int	i;
	int	swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = -1;
		while (++i < size - 1)
		{
			if (ft_strcmp(copy[i], copy[i + 1]) > 0)
			{
				ft_swap(&copy[i], &copy[i + 1], sizeof(char *));
				swapped = 1;
			}
		}
	}
}

static void	print_env_copy(char **copy)
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
			printf("%.*s", (int)(value - copy[i] + 1), copy[i]);
			value++;
			printf("\"%s\"", value);
		}
		else
			printf("%s", copy[i]);
		printf("\n");
	}
}

static void	print_sorted_env(char **env)
{
	char	**copy;
	int		size;

	size = 0;
	while (env[size])
		size++;
	copy = ft_arrdup(env, size + 1);
	if (!copy)
		return (perror("malloc error"));
	sort_env_copy(copy, size);
	print_env_copy(copy);
	ft_arrfree(copy);
}

static int	handle_export_arg(char ***env, char *arg)
{
	char	*name;
	char	*value;
	char	*new_value;
	int		result;

	value = ft_strchr(arg, '=');
	if (value)
	{
		name = ft_substr(arg, 0, value - arg);
		value++;
		new_value = ft_strdup(value);
	}
	else
	{
		name = ft_strdup(arg);
		new_value = ft_strdup("");
	}
	if (!is_valid_name(name))
	{
		free(name);
		free(new_value);
		return (1);
	}
	result = update_env_var(env, name, new_value);
	free(name);
	free(new_value);
	return (result);
}

int	ft_export(char ***env, char **args)
{
	int	i;
	int	ret;
	int	j;

	j = 0;
	while (args[j])
	{
		printf("DEBUG: args[%d] = '%s'\n", j, args[j]);
		j++;
	}
	if (!args[1])
		return (print_sorted_env(*env), 0);
	ret = 0;
	i = 1;
	while (args[i])
	{
		printf("DEBUG: Checking identifier: %s\n", args[i]);
		if (!is_valid_identifier(args[i]))
		{
			printf("DEBUG: Invalid identifier detected: %s\n", args[i]);
			perror("export: invalid identifier\n");
			ret = 1;
		}
		else if (handle_export_arg(env, args[i]) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int ft_export(char **env, char **args);
// char **copy_env(char **env);
// void cleanup_env(char **env);
// void print_sorted_env(char **env);

// int main(void)
// {
//     char *base_env[] = {
//         "PATH=/usr/bin",
//         "USER=testuser",
//         "SHELL=/bin/bash",
//         NULL
//     };
//     char **env = copy_env(base_env);
//     char *test_cases[] = {
//         "export",               // 1. Leeres Export
//         "export VALID=123",     // 2. Gültige Variable
//         "export INVALID-NAME",  // 3. Ungültiger Name
//         "export _UNDER=SCORE",  // 4. Unterstriche
//         "export EMPTY=",        // 5. Leerer Wert
//         "export 123INVALID=no", // 6. Zahl am Anfang
//         "export SPECIAL='$PATH'",//7. Sonderzeichen
//         NULL
//     };
//     printf("=== Starting export Tests ===\n\n");
//     for (int i = 0; test_cases[i]; i++)
//     {
//         printf("Test %d: %s\n", i+1, test_cases[i]);
//         char **args = ft_split(test_cases[i], ' ');
//         int result = ft_export(env, args);
//         printf("Return Code: %d\n", result);
//         printf("Current Environment:\n");
//         print_sorted_env(env);
//         printf("----------------------\n\n");
//         free(args);
//     }
//     cleanup_env(env);
//     return 0;
// }
