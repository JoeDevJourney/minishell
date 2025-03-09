/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 13:23:36 by dchrysov         ###   ########.fr       */
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
	inp->cmd = NULL;
	inp->tok = NULL;
	// errno = 0;
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
 * @note It doesn't work for commands with mixed operators.
 */
bool	valid_oper(char **cmd, char *del)
{
	int		i;
	int		size;
	char	*input;
	char	**arr;
	char	*trimmed;

	arr = ft_split2(*cmd, del);
	size = count_array_size(arr);
	i = -1;
	while (arr[++i])
	{
		trimmed = ft_strtrim(arr[i], " ");
		free(arr[i]);
		arr[i] = trimmed;
	}
	i = -1;
	while (++i < size)
	{
		if (i < size - 1 && arr[i][0] == '\0')
			return (
				printf("bash: syntax error near unexpected token `%s'\n", del),
				false);
		if (i == size - 1 && arr[i][0] == '\0')
		{
			input = readline("");
			*cmd = ft_strjoin_free(*cmd, input);
			free(input);
		}
	}
	return (true);
}

void	update_shell_lvl(t_data *inp)
{
	int		lvl;
	char	*shlvl_val;
	char	*lvl_str;

	lvl = 1;
	shlvl_val = get_env_val(*inp, "SHLVL");
	if (shlvl_val)
		lvl = ft_atoi(shlvl_val) + 1;
	lvl_str = ft_itoa(lvl);
	if (lvl_str)
	{
		update_env_var(&inp->env, "SHLVL", lvl_str);
		free(lvl_str);
	}
}
