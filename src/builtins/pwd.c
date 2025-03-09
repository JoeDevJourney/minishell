/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/08 21:08:46 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pwd(t_data inp)
{
	if (inp.tok[1] == NULL
		|| !ft_strncmp(inp.tok[1], "-L", ft_strlen(inp.tok[1])))
		return (printf("%s\n", get_env_val(inp, "PWD")), 0);
	else
		return (perror(inp.tok[0]), 1);
}
