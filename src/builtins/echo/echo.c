/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/21 20:14:05 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	join_n_print(char **arr, bool newline)
{
	char	*line;
	char	*new_line;
	int		res;

	if (!arr || !*arr)
		return (0);
	line = *arr++;
	while (*arr)
	{
		new_line = ft_strjoin(line, " ");
		if (!new_line)
			return (-1);
		free(line);
		line = new_line;
		new_line = ft_strjoin(line, *arr);
		if (!new_line)
			return (-1);
		free(line);
		line = new_line;
		arr++;
	}
	if (newline)
		line = ft_strjoin(line, "\n");
	res = printf("%s", line);
	return (free(line), res);
}

int	echo(char **str, bool upper)
{
	if (**str == '-')
	{
		if (!ft_strncmp(*str, "-n", ft_strlen(*str)))
		{
			if (upper)
				return (join_n_print(++str, 0));
			else
			{
				while (!ft_strncmp(*str, "-n", ft_strlen(*str)))
					str++;
				return (join_n_print(str, 0));
			}
		}
		else if (!ft_strncmp(*str, "-nn", ft_strlen(*str)))
		{
			if (upper)
				return (join_n_print(str, 1));
			else
			{
				while (!ft_strncmp(*str, "-nn", ft_strlen(*str)))
					str++;
				return (join_n_print(str, 0));
			}
		}
		return (join_n_print(str, 1));
	}
	return (join_n_print(str, 1));
}

int	main(int argc, char **argv)
{
	char	**token;

	(void) argc;
	token = ft_split(argv[2], ' ');
	if (!ft_strncmp(argv[1], "echo", ft_strlen(argv[1])))
		echo(token, false);
	if (!ft_strncmp(argv[1], "Echo", ft_strlen(argv[1])))
		echo(token, true);
}

