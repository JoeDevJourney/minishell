/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 20:02:38 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Handles uppercase 'echo', supports -n flag.
 * 
 * @param arr Array of arguments.
 * @return int Exit status.
 */
static int	upper_echo(char **arr)
{
	bool	nl_flag;
	char	*res;

	pause();
	if (!arr || !*arr)
		return (printf("\n"), 0);
	nl_flag = false;
	if (!ft_strncmp(arr[0], "-n", 2) && ft_strlen(arr[0]) == 2)
	{
		res = join_cmd(&arr[1], " ");
		nl_flag = true;
	}
	else
		res = join_cmd(&arr[0], " ");
	printf("%s", res);
	if (!nl_flag)
		printf("\n");
	return (free(res), 0);
}

/**
 * @brief Handles lowercase 'echo', supports multiple -n flags.
 * 
 * @param arr Array of arguments.
 * @return int Exit status.
 */
static int	lower_echo(char **arr)
{
	bool	nl_flag;
	char	*res;
	int		start;

	nl_flag = true;
	if (!arr || !*arr)
		return (printf("\n"), 0);
	start = parse_n_flag(arr, &nl_flag);
	if (!arr[start])
		return (0);
	res = join_cmd(&arr[start], " ");
	printf("%s", res);
	if (nl_flag)
		printf("\n");
	return (free(res), 0);
}

/**
 * @brief Executes the echo builtin, dispatching to upper/lower echo.
 * 
 * @param cmd Array of command arguments.
 * @return int Exit status.
 */
int	exec_echo(char **cmd)
{
	int		i;
	bool	flag;

	i = -1;
	flag = false;
	while (cmd[0][++i])
	{
		if (cmd[0][i] >= 'A' && cmd[0][i] <= 'Z')
		{
			flag = true;
			break ;
		}
	}
	if (flag)
		return (upper_echo(&cmd[1]));
	return (lower_echo(&cmd[1]));
}
