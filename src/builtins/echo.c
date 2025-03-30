/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/30 22:03:39 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static int	lower_echo(char **arr)
{
	bool	nl_flag;
	char	*res;
	int		i;
	int		j;

	if (!arr || !*arr)
		return (printf("\n"), 0);
	nl_flag = false;
	i = 0;
	while (arr[i] && arr[i][0] == '-')
	{
		j = 1;
		while (arr[i][j] == 'n')
			j++;
		if (arr[i][j] != '\0')
			break ;
		i++;
		nl_flag = true;
	}
	if (!arr[i])
		return (0);
	res = join_cmd(&arr[i], " ");
	printf("%s", res);
	if (!nl_flag)
		printf("\n");
	return (free(res), 0);
}

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
