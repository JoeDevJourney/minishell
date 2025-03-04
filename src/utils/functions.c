/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/04 15:40:49 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Initializes redir struct variables
 */
void	init_redir(t_data *inp)
{
	inp->inp_op.cmd = NULL;
	inp->inp_op.fd = NULL;
	inp->inp_op.num_cmd = 0;
	inp->app_op.cmd = NULL;
	inp->app_op.fd = NULL;
	inp->app_op.num_cmd = 0;
	inp->out_op.cmd = NULL;
	inp->out_op.fd = NULL;
	inp->out_op.num_cmd = 0;
	inp->hdoc_op.cmd = NULL;
	inp->hdoc_op.fd = NULL;
	inp->hdoc_op.num_cmd = 0;
	inp->input = NULL;
	inp->command = NULL;
	errno = 0;
}

/**
 * @brief Joins 3 str together
 */
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

/**
 * @brief Checks if there's a hanging command near an operator
 * 
 * @param str The address of the input as a str
 * @param dl The operator as a delimeter 
 */
bool	valid_oper(char **str, char *dl)
{
	char	**arr;
	char	*ptr;
	char	*cmd;
	int		i;
	int		size;

	arr = ft_split2(*str, dl);
	size = count_array_size(arr);
	i = -1;
	while (++i < size)
	{
		ptr = ft_strtrim(arr[i], " ");
		if (*ptr == '\0')
		{
			if (i < size - 1)
				return (printf("syntax error near unexpected token `%s'\n", dl), 0);
			else
			{
				cmd = readline("> ");
				while (!*cmd)
					cmd = readline("> ");
				free(ptr);
				ptr = ft_strjoin(*str, cmd);
				free(*str);
				*str = ft_strdup(ptr);
				free(cmd);
			}
		}
		free(ptr);
	}
	return (free_array(arr), 1);
}

void	expand_redir(t_data *inp)
{
	if (inp->inp_op.cmd && *inp->inp_op.cmd)
		expnd_quotes(&inp->inp_op.cmd, &inp->env, NULL);
	if (inp->out_op.cmd && *inp->out_op.cmd)
		expnd_quotes(&inp->out_op.cmd, &inp->env, NULL);
	if (inp->app_op.cmd && *inp->app_op.cmd)
		expnd_quotes(&inp->app_op.cmd, &inp->env, NULL);
	// if (inp->hdoc_op.cmd && *inp->hdoc_op.cmd)
	// 	expnd_quotes(&inp->hdoc_op.cmd, &inp->env, expansion_oper);
}
