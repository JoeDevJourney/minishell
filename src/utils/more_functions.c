/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:11:46 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/13 20:55:55 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_with_error(char *msg, int ret_val)
{
	perror(msg);
	exit(ret_val);
}

void	free_input(t_data *inp)
{
	if (inp->and.cmd && *inp->and.cmd)
		free_array(inp->and.cmd);
	if (inp->or.cmd && *inp->or.cmd)
		free_array(inp->or.cmd);
	if (inp->pipe.cmd && *inp->pipe.cmd)
		free_array(inp->pipe.cmd);
	// if (inp->redir.cmd && *inp->redir.cmd)
	// 	free_array(inp->redir.cmd);
	free(inp->input);
}
