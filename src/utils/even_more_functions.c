/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 21:52:16 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_array(char ***arr, int size)
{
	int	i;

	i = -1;
	if (!arr || !*arr)
		return ;
	while (++i < size)
		free((*arr)[i]);
	free (*arr);
	*arr = NULL;
}

void	free_array_fd(int **fd)
{
	int	i;

	if (!fd)
		return ;
	i = 0;
	while (fd[i])
		i++;
	while (i-- > 0)
		free(fd[i]);
	free(fd);
	fd = NULL;
}

void	free_commands(t_data *inp)
{
	if (inp->input)
		free(inp->input);
	inp->input = NULL;
	if (inp->cmd)
		free(inp->cmd);
	inp->cmd = NULL;
	free_array(&inp->pipe.cmd, inp->pipe.num_cmd);
	inp->pipe.cmd = NULL;
	free_array(&inp->tok, count_array_size(inp->tok));
	inp->tok = NULL;
}

void	free_redir(t_data *inp)
{
	t_redir_op	*oper_arr[4];
	int			i;

	oper_arr[0] = &inp->inp_op;
	oper_arr[1] = &inp->app_op;
	oper_arr[2] = &inp->out_op;
	oper_arr[3] = &inp->hdoc_op;
	i = -1;
	while (++i < 4)
		free_array(&oper_arr[i]->cmd, oper_arr[i]->num_cmd);
	init_redir(inp);
}

void	free_struct(t_data *inp, bool pipe_flag)
{
	free_commands(inp);
	if (pipe_flag)
	{
		if (inp->pipe.fd)
			free_array_fd(inp->pipe.fd);
		free(inp->home_dir);
		free_env_list(inp->env);
	}
	free_redir(inp);
}

// void	print_data(t_data inp)
// {
// 	printf("input: '%s'\n", inp.input);
// 	printf("pipe[%d]: [", inp.pipe.num_cmd);
// 	while (inp.pipe.cmd && *inp.pipe.cmd)
// 		printf("'%s', ", *inp.pipe.cmd++);
// 	printf("]\n");
// 	printf("hdoc[%d]: [", inp.hdoc_op.num_cmd);
// 	while (inp.hdoc_op.cmd && *inp.hdoc_op.cmd)
// 		printf("'%s', ", *inp.hdoc_op.cmd++);
// 	printf("]\n");
// 	printf("inp[%d]: [", inp.hdoc_op.num_cmd);
// 	while (inp.inp_op.cmd && *inp.inp_op.cmd)
// 		printf("'%s', ", *inp.inp_op.cmd++);
// 	printf("]\n");
// 	printf("out[%d]: [", inp.out_op.num_cmd);
// 	while (inp.out_op.cmd && *inp.out_op.cmd)
// 		printf("'%s', ", *inp.out_op.cmd++);
// 	printf("]\n");
// 	printf("app[%d]: [", inp.app_op.num_cmd);
// 	while (inp.app_op.cmd && *inp.app_op.cmd)
// 		printf("'%s', ", *inp.app_op.cmd++);
// 	printf("]\n");
// 	printf("cmd: '%s'\n", inp.cmd);
// 	printf("tok[%zu]: [", count_array_size(inp.tok));
// 	while (inp.tok && *inp.tok)
// 		printf("'%s', ", *inp.tok++);
// 	printf("]\n\n");
// }
