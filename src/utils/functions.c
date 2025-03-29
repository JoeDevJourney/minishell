/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/27 15:19:46 by dchrysov         ###   ########.fr       */
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
 * @brief Hdoc expansion and writing to the file based on quotes in the del
 */
void	write_to_fd(char **input, t_data *inp, int i)
{
	check_open_quotes(&inp->hdoc_op.cmd[i]);
	if (ft_strchr(inp->hdoc_op.cmd[i], '"')
		|| ft_strchr(inp->hdoc_op.cmd[i], '\''))
		ft_putendl_fd(*input, *inp->hdoc_op.fd[1]);
	else
	{
		expansion(input, *inp);
		ft_putendl_fd(*input, *inp->hdoc_op.fd[1]);
	}
}

char	**list_to_array(t_env *head)
{
	int		count;
	t_env	*temp;
	char	**arr;
	int		i;

	count = 0;
	temp = head;
	i = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	arr = safe_malloc((count + 1) * sizeof(char *));
	while (head)
	{
		arr[i] = ft_strjoin3(head->name, "=", head->value);
		i++;
		head = head->next;
	}
	arr[i] = NULL;
	return (arr);
}

int	count_delim(char *str, char *delim)
{
	int		count;
	int		i;
	bool	open_sq;
	bool	open_dq;

	i = -1;
	count = 1;
	open_sq = false;
	open_dq = false;
	while (str && str[++i])
	{
		if (str[i] == '\'' && !open_dq)
			open_sq = !open_sq;
		else if (str[i] == '"' && !open_sq)
			open_dq = !open_dq;
		if (!open_sq && !open_dq && ft_strchr(delim, str[i]))
			count++;
	}
	return (count);
}
