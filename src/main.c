/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitris <dimitris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2024/10/19 23:23:18 by dimitris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(void)
{
	char	*cmd;

	printf("Welcome\n");
	while ((cmd = readline("Enter command: ")))
	{
		if (cmd && *cmd)
		{
			add_history(cmd);
			if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
				printf("%s\n", getenv("PWD"));
			// else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
			// else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
			// else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
			// else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
			// else if (!ft_strncmp(cmd, "$?", ft_strlen(cmd)))
		}
	}
}
