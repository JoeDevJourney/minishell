/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/29 20:30:46 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Executes the pwd builtin, printing the current working directory.
 * 
 * @param inp Main data structure.
 * @return int Exit status.
 */
int	exec_pwd(t_data inp)
{
	char	*temp;

	temp = get_env_val(inp, "PWD");
	if (inp.tok[1] && inp.tok[1][0] == '-')
		if (inp.tok[0][1] != 'L')
			return (errno = EINVAL, perror(*inp.tok), free(temp), 1);
	return (printf("%s\n", temp), free(temp), 0);
}
