/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:38:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/04 11:54:48 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Merges the strings of an arr back together, separated by the del
 */
char	*join_cmd(char **arr, char *del)
{
	char	*res;
	char	*with_space;
	int		i;

	i = 0;
	res = ft_strdup(arr[i]);
	while (arr[++i])
	{
		with_space = ft_strjoin(res, del);
		free(res);
		res = ft_strjoin(with_space, arr[i]);
		free(with_space);
	}
	return (res);
}

static void	ask_for_quote(char **str, char quote)
{
	char	*temp;
	char	*rem;

	while (1)
	{
		temp = ft_strjoin(*str, "\n");
		rem = readline("> ");
		free(*str);
		*str = ft_strjoin(temp, rem);
		free(temp);
		if (ft_strchr(rem, quote))
		{
			free(rem);
			break ;
		}
		free(rem);
	}
}

void	check_open_quotes(char **str, char quote)
{
	int		i;
	int		num;

	i = -1;
	num = 0;
	while ((*str)[++i])
		if ((*str)[i] == quote)
			num++;
	if (num % 2 != 0)
		ask_for_quote(str, quote);
}

/**
 * @brief Takes input the address of an arr, goes through all of its strings,
 * looking for quotes, executing the appropriate f in every case.
 */
void	expnd_quotes(char ***arr, char ***env, void (*f)(char **, char ***))
{
	int	i;

	i = 0;
	if (!(*arr)[i])
		return ;
	while ((*arr)[i])
	{
		if (ft_strchr((*arr)[i], '"')
			|| (!ft_strchr((*arr)[i], '"') && !ft_strchr((*arr)[i], '\'')))
			handle_quote(&(*arr)[i], *env, '"');
		else if (ft_strchr((*arr)[i], '\''))
			handle_quote(&(*arr)[i], *env, '\'');
		if (f)
			f(&(*arr)[i], env);
		i++;
	}
}


// int main(int argc, char **argv, char **env)
// {
// 	char *str = ft_strdup("Hello $PWD malaka!");

// 	(void)argc;
// 	(void)argv;
// 	printf("\nbefore: '%s'\n", str);
// 	expansion_oper(env, &str);
// 	printf("after: '%s'\n\n", str);
// 	free(str);
// }

// cc *.c ../builtins/cd/cd_utils.c ../../include/libft/src/*.c -o quote_utils -Wall -Werror -Wextra -g -lreadline
