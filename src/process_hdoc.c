/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:07:25 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 14:16:07 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Checks for quotes in the delimeter
 * 
 * @returns the delimeter trimmed of quotes
 * 
 * @note return 1 if there were quotes in the first place, 0 otherwise
 */
static bool	trim_delimeter(char **del)
{
	char	*trimmed;
	bool	res;

	check_open_quotes(del);
	res = false;
	while (ft_strchr(*del, '\''))
	{
		trimmed = ft_strtrim(*del, "'");
		free(*del);
		*del = ft_strtrim(trimmed, "'");
		free(trimmed);
		res = true;
	}
	while (ft_strchr(*del, '"'))
	{
		trimmed = ft_strtrim(*del, "\"");
		free(*del);
		*del = ft_strtrim(trimmed, "\"");
		free(trimmed);
		res = true;
	}
	return (res);
}

static void	hdoc_prompt(t_data *inp, int i)
{
	char	*input;
	bool	q_flag;

	if (trim_delimeter(&inp->hdoc_op.cmd[i]))
		q_flag = true;
	else
		q_flag = false;
	input = NULL;
	while (1)
	{
		if (input)
			free(input);
		input = readline("> ");
		if (!ft_strncmp(input, inp->hdoc_op.cmd[i], ft_strlen(input))
			&& ft_strlen(input) == ft_strlen(inp->hdoc_op.cmd[i]))
			break ;
		if (!q_flag)
			expansion(&input, *inp);
		ft_putendl_fd(input, *inp->hdoc_op.fd[1]);
	}
	free(input);
}

/**
 * @note Need to add the expansion functionality in the user input
 */
bool	hdoc_oper(t_data *inp)
{
	static size_t	i;
	char			*hdoc;

	hdoc = ft_strjoin(inp->home_dir, "/obj/heredoc");
	inp->hdoc_op.fd = safe_malloc(3 * sizeof(int *));
	inp->hdoc_op.fd[0] = safe_malloc(sizeof(int));
	*inp->hdoc_op.fd[0] = STDIN_FILENO;
	inp->hdoc_op.fd[1] = safe_malloc(sizeof(int));
	*inp->hdoc_op.fd[1] = open(hdoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*inp->hdoc_op.fd[1] == -1)
		return (perror(inp->hdoc_op.cmd[i]), false);
	inp->hdoc_op.fd[2] = NULL;
	hdoc_prompt(inp, i);
	close(*inp->hdoc_op.fd[1]);
	*inp->hdoc_op.fd[1] = open(hdoc, O_RDONLY);
	if (!inp->hdoc_op.cmd[++i])
		dup2(*inp->hdoc_op.fd[1], *inp->hdoc_op.fd[0]);
	if (i == count_array_size(inp->hdoc_op.cmd))
		i = 0;
	return (close(*inp->hdoc_op.fd[1]),
		free_array_fd(inp->hdoc_op.fd), free(hdoc), true);
}

