/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/20 19:27:42 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	out_oper(t_data *inp)
{
	static size_t	i;

	inp->out_op.fd = safe_malloc(3 * sizeof(int *));
	inp->out_op.fd[0] = safe_malloc(sizeof(int));
	inp->out_op.fd[1] = safe_malloc(sizeof(int));
	inp->out_op.fd[2] = NULL;
	*inp->out_op.fd[0] = STDOUT_FILENO;
	*inp->out_op.fd[1] = open(inp->out_op.cmd[i],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*inp->out_op.fd[1] == -1)
		return (perror(inp->out_op.cmd[i]), false);
	if (!inp->out_op.cmd[++i])
		dup2(*inp->out_op.fd[1], *inp->out_op.fd[0]);
	close(*inp->out_op.fd[1]);
	free_array_fd(inp->out_op.fd);
	if (i == count_array_size(inp->out_op.cmd))
		i = 0;
	return (true);
}

static bool	inp_oper(t_data *inp)
{
	static size_t	i;

	inp->inp_op.fd = safe_malloc(3 * sizeof(int *));
	inp->inp_op.fd[0] = safe_malloc(sizeof(int));
	*inp->inp_op.fd[0] = STDIN_FILENO;
	inp->inp_op.fd[1] = safe_malloc(sizeof(int));
	*inp->inp_op.fd[1] = open(inp->inp_op.cmd[i], O_RDONLY);
	if (*inp->inp_op.fd[1] == -1)
		return (perror(inp->inp_op.cmd[i]), false);
	inp->inp_op.fd[2] = NULL;
	if (!inp->inp_op.cmd[++i])
		dup2(*inp->inp_op.fd[1], *inp->inp_op.fd[0]);
	close(*inp->inp_op.fd[1]);
	free_array_fd(inp->inp_op.fd);
	if (i == count_array_size(inp->inp_op.cmd))
		i = 0;
	return (true);
}

static bool	app_oper(t_data *inp)
{
	static size_t	i;

	inp->app_op.fd = safe_malloc(3 * sizeof(int *));
	inp->app_op.fd[0] = safe_malloc(sizeof(int));
	inp->app_op.fd[1] = safe_malloc(sizeof(int));
	inp->app_op.fd[2] = NULL;
	*inp->app_op.fd[0] = STDOUT_FILENO;
	*inp->app_op.fd[1] = open(inp->app_op.cmd[i],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*inp->app_op.fd[1] == -1)
		return (perror(inp->app_op.cmd[i]), false);
	if (!inp->app_op.cmd[++i])
		dup2(*inp->app_op.fd[1], *inp->app_op.fd[0]);
	close(*inp->app_op.fd[1]);
	free_array_fd(inp->app_op.fd);
	if (i == count_array_size(inp->app_op.cmd))
		i = 0;
	return (true);
}

/**
 * @brief Takes the (char *)inp->cmd and executes the appropriate redirection
 * based on the (char **)inp->tok 
 * 
 * @note In all the individual redir functions, fd[0] is for the std fd and
 * fd[1] is the one to be redirected to. 
 * 
 * @returns 1 in case of valid redir, 0 otherwise 
 */
bool	process_fds(t_data *inp)
{
	int		i;
	bool	open_sq;
	bool	open_dq;
	bool	res;

	i = -1;
	res = true;
	open_sq = false;
	open_dq = false;
	while (inp->pipe.cmd && (*inp->pipe.cmd)[++i] && res)
	{
		if ((*inp->pipe.cmd)[i] == '\'' && !open_dq)
			open_sq = !open_sq;
		if ((*inp->pipe.cmd)[i] == '"' && !open_sq)
			open_dq = !open_dq;
		if ((*inp->pipe.cmd)[i] == '<' && !open_dq && !open_sq)
		{
			if ((*inp->pipe.cmd)[++i] == '<')
				res = hdoc_oper(inp);
			else
				res = inp_oper(inp);
		}
		else if ((*inp->pipe.cmd)[i] == '>' && !open_dq && !open_sq)
		{
			if ((*inp->pipe.cmd)[++i] == '>')
				res = app_oper(inp);
			else
				res = out_oper(inp);
		}
	}
	return (res);
}

/**
 * @brief Expands all redir operators, keeping any quotes, except for the hdoc
 * 
 * @note The fds won't be tokenized, cause it messes with their execution.
 * Instead they are trimmed for both single and double quotes.
 * Hdoc is handled speacially.
 */
void	expand_redir(t_data *inp)
{
	int		arr_i;
	int		str_i;
	char	*trimmed;
	char	**arr[4];

	arr[0] = inp->inp_op.cmd;
	arr[1] = inp->out_op.cmd;
	arr[2] = inp->app_op.cmd;
	arr[3] = NULL;
	arr_i = -1;
	while (arr[++arr_i])
	{
		str_i = -1;
		while (arr[arr_i][++str_i])
		{
			expansion(&arr[arr_i][str_i], *inp);
			trimmed = ft_strtrim(arr[arr_i][str_i], "\"");
			free(arr[arr_i][str_i]);
			arr[arr_i][str_i] = trimmed;
			trimmed = ft_strtrim(arr[arr_i][str_i], "'");
			free(arr[arr_i][str_i]);
			arr[arr_i][str_i] = trimmed;
		}
	}
}
