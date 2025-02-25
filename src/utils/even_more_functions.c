/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/24 15:30:02 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	inp->input = NULL;
	inp->command = NULL;
	errno = 0;
}

void	free_array(char **arr)
{
	char	**temp;

	temp = arr;
	while (*temp)
		free(*temp++);
	free (arr);
	arr = NULL;
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
}

void	free_commands(t_data *inp)
{
	if (inp->input && *inp->input)
		free(inp->input);
	if (inp->command && *inp->command)
		free_array(inp->command);
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
	{
		if (oper_arr[i]->cmd && *oper_arr[i]->cmd)
		{
			free_array(oper_arr[i]->cmd);
			free_array_fd(oper_arr[i]->fd);
		}
	}
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
	printf("input: '%s'\n", inp.input);
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
	printf("]\n\n");
	pause();
}
