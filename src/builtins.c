/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/20 18:58:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo(char **str, bool upper)
{
	char	**ptr;
	// char	*line;

	(void) upper;
	ptr = str;
	while (*(ptr + 1))
	// if (ft_strncmp(str[0], "-n", ft_strlen(str[0])))
	if (!ft_strncmp(str[0], "-n", ft_strlen(str[0])))
	{
		printf("\'%s \'", *++ptr);
		printf("\n");
	}
	return (0);
}

int	main(void)
{
	char	*str = "-n Hello mr malaka";
	char	**token;
	int		res;

	(void)res;
	token = ft_split(str, ' ');
	// while (*ptr)
	// 	printf("token[%d]: \'%s\'\n", j++, *ptr++);
	res = echo(token, false);
}

// int	cd()

// int	export()

// int	exit()

// int	unset()