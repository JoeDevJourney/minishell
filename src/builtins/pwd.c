/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 21:58:49 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pwd(t_data inp)
{
	if (inp.tok[1] && inp.tok[1][0] == '-')
		if (inp.tok[0][1] != 'L')
			return (errno = EINVAL, perror(*inp.tok), 1);
	return (printf("%s\n", get_env_val(inp, "PWD")), 0);
}
