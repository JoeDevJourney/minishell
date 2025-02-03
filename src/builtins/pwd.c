/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/03 17:14:48 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @note There is something wrong with the return value
 */
int	exec_pwd(char **cmd)
{
	(void)cmd;
	// if (!ft_strncmp(cmd[1],"-L", ft_strlen(cmd[1])))				(?)
	// else if (!ft_strncmp(cmd[1],"-P", ft_strlen(cmd[1])))
	// else
	printf("%s\n", getenv("PWD"));
	return (0);
}
