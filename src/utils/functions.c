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
 * @brief Initializes redirection operator struct variables.
 * 
 * @param inp Pointer to main data structure.
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
 * @brief Joins three strings together.
 * 
 * @param s1 First string.
 * @param s2 Second string.
 * @param s3 Third string.
 * @return char* Joined string (allocated).
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
 * @brief Handles heredoc expansion and writes to file based on quotes 
 * in delimiter.
 * 
 * @param input Pointer to input string.
 * @param inp Pointer to main data structure.
 * @param i Index of heredoc command.
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

/**
 * @brief Converts environment list to array of strings.
 * 
 * @param head Head of environment list.
 * @return char** Array of environment strings.
 */
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

/**
 * @brief Counts the number of delimiters in a string, respecting quotes.
 * 
 * @param str Input string.
 * @param delim Delimiter string.
 * @return int Number of delimiters found.
 */
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
