/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:11 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/05 18:29:11 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	repl_env_value(char *src, char **dst, int *src_i, int *dst_i, char **env)
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

/**
 * @brief Expands env values of the string keeping the quotes, 
 */
static void	seg_expansion(char **str, char **env)
{
	char	*env_val;
	int		dest_pos;
	int		src_pos;

	dest_pos = 0;
	src_pos = 0;
	env_val = safe_malloc(1024);
	while ((*str)[src_pos])
	{
		if ((*str)[src_pos] == '$')
			repl_env_value((*str), &env_val, &src_pos, &dest_pos, env);
		else if ((*str)[src_pos] == '\\')
		{
			src_pos++;
			env_val[dest_pos++] = (*str)[src_pos++];
		}
		else
			if (dest_pos < 1023)
				env_val[dest_pos++] = (*str)[src_pos++];
	}
	env_val[dest_pos] = '\0';
	free(*str);
	*str = ft_strdup(env_val);
	free(env_val);
}

/**
 * @brief Given a delimeter to mark the end of the segment, it checks for
 * expansion operators and expands their values.
 */
static void	expand_segment(char **str, int *i, char del, char **env)
{
	int		len;
	char	*prefix;
	char	*seg;
	char	*remainder;

	prefix = safe_malloc(*i + 1);
	ft_strlcpy(prefix, *str, *i + 1);
	seg = *str + *i;
	len = 1;
	while (seg[len] && seg[len] != del)
		len++ ;
	seg = safe_malloc(len + 1);
	ft_strlcpy(seg, *str + *i, len + 1);
	seg_expansion(&seg, env);
	remainder = ft_strdup(*str + *i + len);
	*i += ft_strlen(seg) - 1;
	free(*str);
	*str = safe_malloc(ft_strlen(seg) + ft_strlen(remainder) + 1);
	*str = ft_strjoin3(prefix, seg, remainder);
	free(prefix);
	free(remainder);
	free(seg);
}

/**
 * @brief Expands the input str if necessary based on each quote functionality
 */
void	expansion(char **str, char **env)
{
	int		i;
	char	*trimmed;

	trimmed = ft_strtrim(*str, " ");
	free(*str);
	*str = trimmed;
	i = -1;
	while ((*str)[++i])
	{
		while ((*str)[i] == ' ')
			i++;
		if ((*str)[i] == '"')
			expand_segment(str, &i, '"', env);
		else if ((*str)[i] == '\'')
			while ((*str)[++i] != '\'')
				continue ;
		else
			expand_segment(str, &i, ' ', env);
	}
}
