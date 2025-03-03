/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/03 20:22:19 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static int	upper_echo(char **arr, char **env)
// {
// 	bool	newline;
// 	char	*res;
//
// 	if (!arr || !*arr)
// 		return (printf("\n"), 0);
// 	res = NULL;
// 	expnd_quotes(&arr, &env, NULL);
// 	newline = false;
// 	if (!ft_strncmp(arr[0], "-n", 2) && ft_strlen(arr[0]) == 2)
// 	{
// 		res = join_cmd(&arr[1], " ");
// 		newline = true;
// 	}
// 	else
// 		res = join_cmd(&arr[0], " ");
// 	printf("%s\n", res);
// 	if (!newline)
// 		printf("\n");
// 	return (free(res), 0);
// }

// static int	lower_echo(t_data inp)
// {
// 	bool	newline;
// 	char	*res;
// 	int		i;
//
// 	if (!arr || !*arr)
// 		return (printf("\n"), 0);
// 	res = NULL;
// 	expnd_quotes(&inp.command, &inp.env, NULL);
// 	newline = false;
// 	i = 0;
// 	while (!ft_strncmp(arr[i], "-n", 2) && ft_strlen(arr[i]) == 2)
// 	{
// 		i++;
// 		newline = true;
// 	}
// 	res = join_cmd(&arr[i], " ");
// 	printf("%s\n", res);
// 	if (!newline)
// 		printf("\n");
// 	return (free(res), 0);
// }

static bool	upper_check(char *str)
{
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			return (true);
		str++;
	}
	return (false);
}

static void	parse_arguments(char *str, char **env)
{
	char	**dq;

	(void)env;
	dq = ft_split(str, '"');
	while (*dq)
		printf("%s\n", *dq++);
	pause();
}

int	exec_echo(char *str, char **env)
{
	bool	upper;

	parse_arguments(str, env);
	if (upper_check(str))
		upper = true;
	else
		upper = false;
	return (0);
		// return (lower_echo(inp));
	// return (upper_echo(inp));
}

int	main(int argc, char **argv, char **env)
{
	int		res;
	char	*str;

	(void) argc;
	str = join_cmd(++argv, "");
	printf("%s\n", str); pause();
	res = exec_echo(*++argv, env);
	printf("\n-------------\nres: %d\n-------------\n\n", res);
	return (0);
}

// cc echo.c ../../include/libft/src/*.c ../utils/*.c cd/cd_utils.c ../quotes.c -o echo -Wall -Werror -Wextra -lreadline