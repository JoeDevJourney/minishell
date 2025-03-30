/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/30 20:54:45 by dchrysov         ###   ########.fr       */
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
		return (perror(inp->out_op.cmd[i]), close(*inp->out_op.fd[1]),
			free_array_fd(inp->out_op.fd), false);
	if (!inp->out_op.cmd[++i])
		dup2(*inp->out_op.fd[1], *inp->out_op.fd[0]);
	close(*inp->out_op.fd[1]);
	if (i == count_array_size(inp->out_op.cmd))
		i = 0;
	return (free_array_fd(inp->out_op.fd), true);
}

static bool	inp_oper(t_data *inp)
{
	static size_t	i;

	inp->inp_op.fd = safe_malloc(3 * sizeof(int *));
	inp->inp_op.fd[0] = safe_malloc(sizeof(int));
	*inp->inp_op.fd[0] = STDIN_FILENO;
	inp->inp_op.fd[1] = safe_malloc(sizeof(int));
	*inp->inp_op.fd[1] = open(inp->inp_op.cmd[i], O_RDONLY);
	inp->inp_op.fd[2] = NULL;
	if (*inp->inp_op.fd[1] == -1)
		return (perror(inp->inp_op.cmd[i]), close(*inp->inp_op.fd[1]),
			free_array_fd(inp->inp_op.fd), false);
	if (!inp->inp_op.cmd[++i])
		dup2(*inp->inp_op.fd[1], *inp->inp_op.fd[0]);
	close(*inp->inp_op.fd[1]);
	if (i == count_array_size(inp->inp_op.cmd))
		i = 0;
	return (free_array_fd(inp->inp_op.fd), true);
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
		return (perror(inp->app_op.cmd[i]), close(*inp->app_op.fd[1]),
			free_array_fd(inp->app_op.fd), false);
	if (!inp->app_op.cmd[++i])
		dup2(*inp->app_op.fd[1], *inp->app_op.fd[0]);
	close(*inp->app_op.fd[1]);
	if (i == count_array_size(inp->app_op.cmd))
		i = 0;
	return (free_array_fd(inp->app_op.fd), true);
}

static bool	redir_oper(t_data *inp, int *i, char oper)
{
	if (oper == '<')
	{
		if ((*inp->pipe.cmd)[++*i] == oper)
			return (hdoc_oper(inp));
		return (inp_oper(inp));
	}
	if ((*inp->pipe.cmd)[++*i] == oper)
		return (app_oper(inp));
	return (out_oper(inp));
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
			res = redir_oper(inp, &i, '<');
		else if ((*inp->pipe.cmd)[i] == '>' && !open_dq && !open_sq)
			res = redir_oper(inp, &i, '>');
	}
	if (!res)
		inp->ret_val = 1;
	return (res);
}
