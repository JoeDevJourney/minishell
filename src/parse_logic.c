/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:03 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/08 17:55:14 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	tokenize_or(t_data *inp)
{
	static int	j;

	if (!valid_oper(inp, &inp->or.cmd[j], "|"))
		return ;
	inp->pipe.cmd = ft_split2(inp->or.cmd[j], "|");
	inp->pipe.num_cmd = count_substr(inp->or.cmd[j], "|");
	init_redir(inp);
	parse_n_exec(inp);
	free_array(inp->pipe.cmd);
	if (++j >= inp->or.num_cmd || !inp->ret_val)
		return ((void)(j = 0));
	tokenize_or(inp);
}

static void	tokenize_and(t_data *inp)
{
	static int	i;

	inp->or.cmd = ft_split2(inp->and.cmd[i], "||");
	inp->or.num_cmd = count_substr(inp->and.cmd[i], "||");
	tokenize_or(inp);
	free_array(inp->or.cmd);
	if (++i >= inp->and.num_cmd || inp->ret_val)
		return ((void)(i = 0));
	tokenize_and(inp);
}

void	parse_n_tokenize(t_data *inp)
{
	inp->and.cmd = ft_split2(inp->cmd, "&&");
	inp->and.num_cmd = count_substr(inp->cmd, "&&");
	free(inp->cmd);
	tokenize_and(inp);
	free_array(inp->and.cmd);
}
