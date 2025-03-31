/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/31 15:40:33 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_quote(char c, bool *open_sq, bool *open_dq)
{
	if (c == '\'' && !*open_dq)
		*open_sq = !*open_sq;
	if (c == '"' && !*open_sq)
		*open_dq = !*open_dq;
}

int	count_oper(char *str, char oper, bool next)
{
	bool	open_sq;
	bool	open_dq;
	int		count;
	int		i;

	open_sq = false;
	open_dq = false;
	count = 0;
	i = -1;
	while (str[++i])
	{
		check_quote(str[i], &open_sq, &open_dq);
		if (!open_sq && !open_dq)
		{
			if (str[i] == oper)
			{
				if (next && str[i + 1] == oper)
					count++;
				else if (!next && str[i + 1] && str[i + 1] != oper)
					count++;
			}
		}
	}
	return (count);
}

static char	*add_redir_filename(char *str)
{
	int		i;
	int		start;
	int		len;

	i = 0;
	len = 0;
	while (str[i] == ' ')
		i++;
	start = i;
	while (str[i])
	{
		if (ft_isalnum(str[i]) != 1 && str[i] != '_' && str[i] != '-'
			&& str[i] != '.' && str[i] != '$' && str[i] != '/')
			break ;
		len++;
		i++;
	}
	return (ft_substr(str, start, len));
}

static void	create_redir_array(char *str, t_redir_op *op, char c, bool n)
{
	int		j;
	int		i;
	bool	open_sq;
	bool	open_dq;

	open_sq = false;
	open_dq = false;
	op->num_cmd = count_oper(str, c, n);
	op->cmd = safe_malloc((op->num_cmd + 1) * sizeof(char *));
	j = 0;
	i = -1;
	while (str[++i])
	{
		check_quote(str[i], &open_sq, &open_dq);
		if (!open_sq && !open_dq && str[i] == c)
		{
			if (n && str[i + 1] && str[i + 1] == c)
				op->cmd[j++] = add_redir_filename(&str[i + 2]);
			if (i > 0 && !n && str[i + 1] && str[i + 1] != c && str[i - 1] != c)
				op->cmd[j++] = add_redir_filename(&str[i + 1]);
			if (i == 0 && !n && str[i + 1] && str[i + 1] != c)
				op->cmd[j++] = add_redir_filename(&str[i + 1]);
		}
	}
	op->cmd[j] = NULL;
}

void	parse_redir(t_data *inp)
{
	int		i;
	bool	open_sq;
	bool	open_dq;

	i = -1;
	open_sq = false;
	open_dq = false;
	while ((*inp->pipe.cmd)[++i])
	{
		check_quote((*inp->pipe.cmd)[i], &open_sq, &open_dq);
		if (!open_sq && !open_dq && ((*inp->pipe.cmd)[i] == '>'
			|| (*inp->pipe.cmd)[i] == '<'))
			break ;
	}
	if (i == 0)
		inp->cmd = ft_strdup("");
	else
		inp->cmd = ft_substr(*inp->pipe.cmd, 0, i);
	create_redir_array(*inp->pipe.cmd, &inp->inp_op, '<', false);
	create_redir_array(*inp->pipe.cmd, &inp->out_op, '>', false);
	create_redir_array(*inp->pipe.cmd, &inp->hdoc_op, '<', true);
	create_redir_array(*inp->pipe.cmd, &inp->app_op, '>', true);
}

// int	main(void)
// {
// 	t_data	inp;

// 	inp.input = ft_strdup("cat -e <$var");
// 	parse_redir(&inp);
// 	printf("input: '%s'\n", inp.input);
// 	printf("cmd: '%s'\n", inp.cmd);
// 	int i = -1;
// 	while (inp.inp_op.cmd[++i])
// 		printf("inp[%d]: '%s'\n", inp.inp_op.num_cmd, inp.inp_op.cmd[i]);
// 	i = -1;
// 	while (inp.out_op.cmd[++i])
// 		printf("out[%d]: '%s'\n", inp.out_op.num_cmd, inp.out_op.cmd[i]);
// 	i = -1;
// 	while (inp.app_op.cmd[++i])
// 		printf("app[%d]: '%s'\n", inp.app_op.num_cmd, inp.app_op.cmd[i]);
// 	i = -1;
// 	while (inp.hdoc_op.cmd[++i])
// 		printf("hdoc[%d]: '%s'\n", inp.hdoc_op.num_cmd, inp.hdoc_op.cmd[i]);
// 	free_array(inp.inp_op.cmd);
// 	free_array(inp.app_op.cmd);
// 	free_array(inp.out_op.cmd);
// 	free_array(inp.hdoc_op.cmd);
// 	free(inp.input);
// 	free(inp.cmd);
// }
