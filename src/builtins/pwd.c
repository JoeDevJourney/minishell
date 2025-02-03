/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 19:22:52 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_pwd(char **cmd)
{
	(void)cmd;
	// if (!ft_strncmp(cmd[1],"-L", ft_strlen(cmd[1])))				(?)
	// else if (!ft_strncmp(cmd[1],"-P", ft_strlen(cmd[1])))
	// else
	printf("%s\n", getenv("PWD"));
	return (0);
}