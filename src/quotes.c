/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:11 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/26 17:36:56 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	single_quotes(char **str)
{
	char	*res;

	res = ft_strtrim(*str, "'");
	free(*str);
	*str = ft_strdup(res);
	free(res);
}

static void	extract_env_value(char *src, char **dst, int *src_i, int *dst_i, char **env)
{
	int			var_length;
	char		*value;
	char		*var_name;
	int			var_i;

	var_i = ++(*src_i);
	if (src[var_i] == '{')
		var_i++;
	while (ft_isalnum(src[*src_i]) || src[*src_i] == '_')
		(*src_i)++;
	if (src[*src_i] == '}')
		(*src_i)++;
	var_length = *src_i - var_i;
	var_name = ft_substr(src, var_i, var_length);
	value = get_env_val(env, var_name);
	if (value)
		while (*value && *dst_i < 1024 - 1)
			(*dst)[(*dst_i)++] = *value++;
	free(var_name);
}

// static void	escape_char(char **src, int *src_i)
// {
// 	(*src_i)++;
// 	if ()
// }

static void	double_quotes(char **str, char **env)
{
	char	*src;
	char	*buffer;
	int		dest_pos;
	int		src_pos;

	dest_pos = 0;
	src_pos = 0;
	buffer = safe_malloc(1024);
	src = ft_strtrim(*str, "\"");
	while (src[src_pos])
	{
		if (src[src_pos] == '$')
			extract_env_value(src, &buffer, &src_pos, &dest_pos, env);
		else if (src[src_pos] == '\\')
		{
			src_pos++;
			buffer[dest_pos++] = src[src_pos++];
		}
		else
			if (dest_pos < 1023)
				buffer[dest_pos++] = src[src_pos++];
	}
	buffer[dest_pos] = '\0';
	free(*str);
	*str = ft_strdup(buffer);
	free(buffer);
	free(src);
}

// search_quotes() ????

int	main(int argc, char **argv, char **env)
{
	char *str;

	(void)argc;
	(void)argv;
	str = ft_strdup("\"Hello: $USER\\\" it going?\"");
	printf("%s\n", str);
	double_quotes(&str, env);
	printf("%s\n\n", str);
	free(str);
	str = ft_strdup("'Hello: $USER  How\\\"s it going?\\'");
	printf("%s\n", str);
	single_quotes(&str);
	printf("%s\n\n", str);
	free(str);
	// if (check_quotes(&inp))
	// 	return (printf("Error: Quote still open.\n"), 0);

	// handle_quotes(&inp);
	// free_array(inp.pipe.cmd);
	// free_array(inp.env);
}

// cc quotes.c -o quotes utils/*.c builtins/env.c builtins/cd/cd_utils.c ../include/libft/src/*.c -Wall -Wextra -Werror -lreadline
