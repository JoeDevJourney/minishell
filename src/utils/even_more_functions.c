/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/18 17:33:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_array(t_redir_op *arr[], t_data *inp)
{
	arr[0] = &inp->inp_op;
	arr[1] = &inp->app_op;
	arr[2] = &inp->out_op;
	arr[3] = &inp->hdoc_op;
}

void	free_data(t_data *inp)
{
	t_redir_op	*oper_arr[4];
	int			i;

	i = -1;
	init_array(oper_arr, inp);
	while (++i < 4)
	{
		if (oper_arr[i]->cmd && *oper_arr[i]->cmd)
		{
			free_array(oper_arr[i]->cmd);
			free(oper_arr[i]->fd[0]);
			free(oper_arr[i]->fd[1]);
			free(oper_arr[i]->fd);
		}
	}
	free(inp->input);
	free_array(inp->command);
	free_array(inp->pipe.cmd);
	// while (++j < inp->pipe.)
	// 	free(oper_arr[i]->fd[j]);
	// free(oper_arr[i]->fd);
}

void	print_data(t_data inp)
{
	printf("\nand[%d]: [", inp.and.num_cmd);
	while (inp.and.cmd && *inp.and.cmd)
		printf("'%s', ", *inp.and.cmd++);
	printf("]\n");
	printf("or[%d]: [", inp.or.num_cmd);
	while (inp.or.cmd && *inp.or.cmd)
		printf("'%s', ", *inp.or.cmd++);
	printf("]\n");
	printf("pipe[%d]: [", inp.pipe.num_cmd);
	while (inp.pipe.cmd && *inp.pipe.cmd)
		printf("'%s', ", *inp.pipe.cmd++);
	printf("]\n");
	printf("hdoc[%d]: [", inp.hdoc_op.num_cmd);
	while (inp.hdoc_op.cmd && *inp.hdoc_op.cmd)
		printf("'%s', ", *inp.hdoc_op.cmd++);
	printf("]\n");
	printf("inp[%d]: [", inp.hdoc_op.num_cmd);
	while (inp.inp_op.cmd && *inp.inp_op.cmd)
		printf("'%s', ", *inp.inp_op.cmd++);
	printf("]\n");
	printf("out[%d]: [", inp.out_op.num_cmd);
	while (inp.out_op.cmd && *inp.out_op.cmd)
		printf("'%s', ", *inp.out_op.cmd++);
	printf("]\n");
	printf("app[%d]: [", inp.app_op.num_cmd);
	while (inp.app_op.cmd && *inp.app_op.cmd)
		printf("'%s', ", *inp.app_op.cmd++);
	printf("]\n");
	printf("command[%zu]: [", count_array_size(inp.command));
	while (inp.command && *inp.command)
		printf("'%s', ", *inp.command++);
	printf("]\n");
	// pause();
}
