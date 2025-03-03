/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/03 19:13:45 by dchrysov         ###   ########.fr       */
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

static char	**parse_arguments(char *str)
{
	char **tokens = malloc(100 * sizeof(char *));
	int token_count = 0;
	int	i = -1;
	int	len = strlen(str);
	char buffer[1024];
	int buf_index = 0;
	char quote = 0;

	while (++i < len)
	{
		if (isspace(str[i]) && !quote)
		{
			if (buf_index > 0)
			{
				buffer[buf_index] = '\0';
				tokens[token_count++] = strdup(buffer);
				buf_index = 0;
			}
		}
		else if (str[i] == '"' || str[i] == '\'')
		{
			if (quote == str[i])
			{
				buffer[buf_index++] = str[i];
				quote = 0;
			}
			else if (quote == 0)
			{
				quote = str[i];
				buffer[buf_index++] = str[i];
			}
			else
				buffer[buf_index++] = str[i];
		}
		else
			buffer[buf_index++] = str[i];
	}
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		tokens[token_count++] = strdup(buffer);
	}
	tokens[token_count] = NULL;
	return (tokens);
}

int	exec_echo(char *str, char **env)
{
	bool	upper;
	char	**arr;

	(void)env;
	arr = parse_arguments(str);
	while (*arr)
		printf("%s\n", *arr++);
	pause();
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
	t_data	inp;

	(void) argc;
	res = exec_echo(*++argv, env);
	printf("\n-------------\nres: %d\n-------------\n\n", res);
	free_array(inp.pipe.cmd);
	free_array(inp.env);
	return (0);
}

// cc echo.c ../../include/libft/src/*.c ../utils/*.c cd/cd_utils.c ../quotes.c -o echo -Wall -Werror -Wextra -lreadline