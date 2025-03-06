/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:11 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/06 14:04:51 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*repl_env_value(char *src, int *src_i, t_data inp)
{
	int			var_length;
	char		*value;
	char		*var_name;
	int			var_i;

	var_i = ++(*src_i);
	if (src[var_i] == '{')
		var_i++;
	while (ft_isalnum(src[*src_i]) || src[*src_i] == '_' || src[*src_i] == '\?')
		(*src_i)++;
	if (src[*src_i] == '}')
		(*src_i)++;
	var_length = *src_i - var_i;
	var_name = ft_substr(src, var_i, var_length);
	value = get_env_val(inp, var_name);
	return (free(var_name), value);
}

/**
 * @brief Expands env values of the string keeping the quotes, 
 */
static void	seg_expansion(char **str, t_data inp)
{
	char	*env_val;
	int		dest_pos;
	int		src_pos;

	dest_pos = 0;
	src_pos = 0;
	env_val = safe_malloc((1023) * sizeof(char));
	while ((*str)[src_pos])
	{
		if ((*str)[src_pos] == '$')
		{
			ft_strlcpy(env_val + dest_pos,
				repl_env_value(*str, &src_pos, inp), 1023 - dest_pos + 1);
			dest_pos += ft_strlen(env_val);
		}
		else if ((*str)[src_pos] == '\\')
			env_val[dest_pos++] = (*str)[++src_pos, src_pos++];
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
 * xpansion operators and expands their values.
 * 
 * @note When called i points to the del, when exits it points to the
 * last char before the closing del.  
 */
static void	expand_segment(char **str, int *i, char del, t_data inp)
{
	int		len;
	char	*prefix;
	char	*seg;
	char	*remainder;

	prefix = safe_malloc(*i + 1);
	ft_strlcpy(prefix, *str, *i + 1);
	seg = *str + *i;
	len = 0;
	while (seg[++len])
		if (seg[len] == del && seg[len - 1] != '\\')
			break ;
	seg = safe_malloc(len + 1);
	ft_strlcpy(seg, *str + *i, len + 1);
	seg_expansion(&seg, inp);
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
void	expansion(char **str, t_data inp)
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
			expand_segment(str, &i, '"', inp);
		else if ((*str)[i] == '\'')
			while ((*str)[++i] != '\'')
				continue ;
		else
			expand_segment(str, &i, ' ', inp);
	}
}
