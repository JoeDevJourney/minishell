/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/27 16:17:59 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (perror("0 bytes"), NULL);
	ptr = malloc(size);
	if (!ptr)
		exit_with_error("Memory allocation failed", EXIT_FAILURE);
	return (ptr);
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

/**
 * @brief Frees an array of fds of any size
 */
void	free_array_fd(int **fd)
{
	int	i;

	if (!fd)
		return ;
	i = 0;
	while (fd && fd[i])
		i++;
	while (i-- > 0)
		free(fd[i]);
	free(fd);
}

void	free_commands(t_data *inp)
{
	if (inp->pipe.cmd && *inp->pipe.cmd)
		free_array(inp->pipe.cmd);
	inp->pipe.cmd = NULL;
	if (inp->cmd && *inp->cmd)
		free(inp->cmd);
	inp->cmd = NULL;
	if (inp->tok && *inp->tok)
		free_array(inp->tok);
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
	{
		if (oper_arr[i]->cmd && *oper_arr[i]->cmd)
			free_array(oper_arr[i]->cmd);
	}
}

void	print_data(t_data inp)
{
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
	printf("cmd: '%s'\n", inp.cmd);
	printf("tok[%zu]: [", count_array_size(inp.tok));
	while (inp.tok && *inp.tok)
		printf("'%s', ", *inp.tok++);
	printf("]\n\n");
	pause();
}
