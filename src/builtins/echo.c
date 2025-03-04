/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/04 18:01:42 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	upper_echo(char **arr)
{
	bool	nl_flag;
	char	*res;

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
	bool	newline;
	char	*res;
	int		i;

	if (!arr || !*arr)
		return (printf("\n"), 0);
	newline = false;
	i = 0;
	while (!ft_strncmp(arr[i], "-n", 2) && ft_strlen(arr[i]) == 2)
	{
		i++;
		newline = true;
	}
	res = join_cmd(&arr[i], " ");
	printf("%s", res);
	if (!newline)
		printf("\n");
	return (free(res), 0);
}

int	exec_echo(char **cmd)
{
	int		i;

	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i] >= 'A' && cmd[0][i] <= 'Z')
			return (upper_echo(&cmd[1]));
	}
	return (lower_echo(&cmd[1]));
}

// cc echo.c ../../include/libft/src/*.c ../utils/*.c cd/cd_utils.c ../quotes.c -o echo -Wall -Werror -Wextra -lreadline