/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/22 19:06:03 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_command(char *cmd, char *argv[], char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd, argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		wait(NULL);
	else
		perror("fork");
}

static int	externals(char **str)
{
	char	**input;
	char	**ptr;
	char	*cmd;

	ptr = str;
	while (*ptr)
		cmd = ft_strjoin(cmd, ft_strjoin(*ptr++, " "));
	input = ft_split(cmd, ' ');
	free(*input);
	*input = ft_strjoin("/bin/", *str);
	execute_command(*input, input, NULL);
	// free(cmd);
	// while (*input)
	// 	free(*input);
	// free(input);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	externals(++argv);
}

// cc ls.c ../../include/libft/src/ft_strlen.c ../../include/libft/src/ft_split.c ../../include/libft/src/ft_strlcpy.c ../../include/libft/src/ft_strjoin.c ../../include/libft/src/ft_strlcat.c -g -Wall -Werror -Wextra