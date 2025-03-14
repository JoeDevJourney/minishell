/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:07:25 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 13:29:08 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	write_to_fd(char **input, t_data *inp, int i)
{
	char	*trimmed;

	check_open_quotes(&inp->hdoc_op.cmd[i]);
	while (ft_strchr(inp->hdoc_op.cmd[i], '\''))
	{
		trimmed = ft_strtrim(inp->hdoc_op.cmd[i], "'");
		free(inp->hdoc_op.cmd[i]);
		inp->hdoc_op.cmd[i] = ft_strtrim(trimmed, "'");
		free(trimmed);
	}
	while (ft_strchr(inp->hdoc_op.cmd[i], '"'))
	{
		trimmed = ft_strtrim(inp->hdoc_op.cmd[i], "\"");
		free(inp->hdoc_op.cmd[i]);
		inp->hdoc_op.cmd[i] = ft_strtrim(trimmed, "\"");
		free(trimmed);
	}
	if (ft_strchr(inp->hdoc_op.cmd[i], '"')
		|| ft_strchr(inp->hdoc_op.cmd[i], '\''))
		ft_putendl_fd(*input, *inp->hdoc_op.fd[1]);
	else
	{
		expansion(input, *inp);
		ft_putendl_fd(*input, *inp->hdoc_op.fd[1]);
	}
}

static void	hdoc_prompt(t_data *inp, int i)
{
	char	*input;

	input = ft_strdup("\0");
	while (1)
	{
		if (*input != '\0'
			&& !ft_strncmp(input, inp->hdoc_op.cmd[i], ft_strlen(input))
			&& ft_strlen(input) == ft_strlen(inp->hdoc_op.cmd[i]))
			break ;
		free(input);
		input = readline("> ");
		write_to_fd(&input, inp, i);
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

