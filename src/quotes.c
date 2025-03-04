/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:11 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/04 23:27:23 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void	single_quotes(char **str)
{
	char	*res;

	res = ft_strtrim(*str, "'");
	free(*str);
	*str = ft_strdup(res);
	free(res);
}

static void	double_quotes(char **str, char **env)
{
	char	*buffer;
	int		dest_pos;
	int		src_pos;

	dest_pos = 0;
	src_pos = 0;
	buffer = safe_malloc(1024);
	while ((*str)[src_pos])
	{
		if ((*str)[src_pos] == '$')
			extract_env_value((*str), &buffer, &src_pos, &dest_pos, env);
		else if ((*str)[src_pos] == '\\')
		{
			src_pos++;
			buffer[dest_pos++] = (*str)[src_pos++];
		}
		else
			if (dest_pos < 1023)
				buffer[dest_pos++] = (*str)[src_pos++];
	}
	buffer[dest_pos] = '\0';
	free(*str);
	*str = ft_strdup(buffer);
	free(buffer);
}

/**
 * @brief Takes the address of a string and expands it based on its quotes 
 */
void	handle_quote(char **str, char **env, char quote)
{
	char	**arr;
	int		i;

	check_open_quotes(str, quote);
	arr = ft_split(*str, quote);
	i = -1;
	while (arr[++i])
	{
		if (quote == '\'')
			single_quotes(&arr[i]);
		else
			double_quotes(&arr[i], env);
	}
	free(*str);
	*str = join_cmd(arr, "");
}

// cc quotes.c -o quotes utils/*.c builtins/env.c builtins/cd/cd_utils.c ../include/libft/src/*.c -Wall -Wextra -Werror -lreadline
