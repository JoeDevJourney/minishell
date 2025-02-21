/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/21 13:22:18 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @note
 */
int	exec_pwd(char **cmd)
{
	if (cmd[1] == NULL || !ft_strncmp(cmd[1], "-L", ft_strlen(cmd[1])))
		printf("%s\n", getenv("PWD"));
	// else if (!ft_strncmp(cmd[1], "-P", ft_strlen(cmd[1])))
	// {
		
	// }
	else
	{
		perror(*cmd);
		return (1);
	}
	return (0);
}
