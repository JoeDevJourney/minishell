/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 15:40:33 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Checks and toggles quote states for single and double quotes.
 * 
 * @param c Current character.
 * @param open_sq Pointer to single quote state.
 * @param open_dq Pointer to double quote state.
 */
void	check_quote(char c, bool *open_sq, bool *open_dq)
{
	if (c == '\'' && !*open_dq)
		*open_sq = !*open_sq;
	if (c == '"' && !*open_sq)
		*open_dq = !*open_dq;
}

/**
 * @brief Counts the number of redirection operators in a string.
 * 
 * @param str Input string.
 * @param oper Operator character to count ('<' or '>').
 * @param next If true, counts double operators (e.g., '<<' or '>>').
 * @return int Number of operators found.
 */
int	count_oper(char *str, char oper, bool next)
{
	bool	open_sq;
	bool	open_dq;
	int		count;
	int		i;

	open_sq = false;
	open_dq = false;
	count = 0;
	i = -1;
	while (str[++i])
	{
		check_quote(str[i], &open_sq, &open_dq);
		if (!open_sq && !open_dq)
		{
			if (str[i] == oper)
			{
				if (next && str[i + 1] == oper)
					count++;
				else if (!next && str[i + 1] && str[i + 1] != oper)
					count++;
			}
		}
	}
	return (count);
}

/**
 * @brief Extracts the filename following a redirection operator.
 * 
 * @param str Input string starting after the operator.
 * @return char* Extracted filename (allocated).
 */
static char	*add_redir_filename(char *str)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	len = 0;
	while (str[i] == ' ')
		i++;
	start = i;
	while (str[i])
	{
		if (ft_isalnum(str[i]) != 1 && str[i] != '_' && str[i] != '-'
			&& str[i] != '.' && str[i] != '$' && str[i] != '/')
			break ;
		len++;
		i++;
	}
	return (ft_substr(str, start, len));
}

/**
 * @brief Creates an array of filenames for redirection operators.
 * 
 * @param str Input string.
 * @param op Pointer to redirection operator structure.
 * @param c Operator character ('<' or '>').
 * @param n If true, handles double operators.
 */
static void	create_redir_array(char *str, t_redir_op *op, char c, bool n)
{
	int		j;
	int		i;
	bool	open_sq;
	bool	open_dq;

	open_sq = false;
	open_dq = false;
	op->num_cmd = count_oper(str, c, n);
	op->cmd = safe_malloc((op->num_cmd + 1) * sizeof(char *));
	j = 0;
	i = -1;
	while (str[++i])
	{
		check_quote(str[i], &open_sq, &open_dq);
		if (!open_sq && !open_dq && str[i] == c)
		{
			if (n && str[i + 1] && str[i + 1] == c)
				op->cmd[j++] = add_redir_filename(&str[i + 2]);
			if (i > 0 && !n && str[i + 1] && str[i + 1] != c && str[i - 1] != c)
				op->cmd[j++] = add_redir_filename(&str[i + 1]);
			if (i == 0 && !n && str[i + 1] && str[i + 1] != c)
				op->cmd[j++] = add_redir_filename(&str[i + 1]);
		}
	}
	op->cmd[j] = NULL;
}

/**
 * @brief Parses redirection operators and filenames from the command string.
 * 
 * @param inp Pointer to main data structure.
 */
void	parse_redir(t_data *inp)
{
	int		i;
	bool	open_sq;
	bool	open_dq;

	i = -1;
	open_sq = false;
	open_dq = false;
	while ((*inp->pipe.cmd)[++i])
	{
		check_quote((*inp->pipe.cmd)[i], &open_sq, &open_dq);
		if (!open_sq && !open_dq && ((*inp->pipe.cmd)[i] == '>'
			|| (*inp->pipe.cmd)[i] == '<'))
			break ;
	}
	if (i == 0)
		inp->cmd = ft_strdup("");
	else
		inp->cmd = ft_substr(*inp->pipe.cmd, 0, i);
	create_redir_array(*inp->pipe.cmd, &inp->inp_op, '<', false);
	create_redir_array(*inp->pipe.cmd, &inp->out_op, '>', false);
	create_redir_array(*inp->pipe.cmd, &inp->hdoc_op, '<', true);
	create_redir_array(*inp->pipe.cmd, &inp->app_op, '>', true);
}
