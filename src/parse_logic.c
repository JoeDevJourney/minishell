/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:17:03 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/21 17:13:52 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	execute_or_chain(t_data *inp)
{
	static int	j;

	if (!valid_oper(&inp->or.cmd[j], "|"))
		return ;
	inp->pipe.cmd = ft_split2(inp->or.cmd[j], "|");
	inp->pipe.num_cmd = count_substr(inp->or.cmd[j], "|");
	init_redir(inp);
	handle_command(inp);
	free_array(inp->pipe.cmd);
	if (++j >= inp->or.num_cmd || !inp->ret_val)
		return ((void)(j = 0));
	execute_or_chain(inp);
}

static void	execute_and_chain(t_data *inp)
{
	static int	i;

	inp->or.cmd = ft_split2(inp->and.cmd[i], "||");
	inp->or.num_cmd = count_substr(inp->and.cmd[i], "||");
	execute_or_chain(inp);
	if (++i >= inp->and.num_cmd || inp->ret_val)
		return ((void)(i = 0));
	free_array(inp->or.cmd);
	execute_and_chain(inp);
}

void	parse_logic(t_data *inp)
{
	inp->and.cmd = ft_split2(inp->input, "&&");
	inp->and.num_cmd = count_substr(inp->input, "&&");
	free(inp->input);
	execute_and_chain(inp);
	free_array(inp->and.cmd);
}
