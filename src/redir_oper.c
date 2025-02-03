/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_oper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/31 19:12:26 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	inp_oper(char **cmd, char **env)
{
	int		new_fd;
	char	**ptr;
	
	ptr = cmd;
	while (*ptr)
	{
		if (!ft_strncmp(*ptr, "<", ft_strlen(*ptr)))
			break ;
		ptr++;
	}
	new_fd = open(*++ptr, O_RDONLY);
	printf("%s opened\n", *ptr);
	dup2(new_fd, STDIN_FILENO);
	fork_command(cmd, env);
	dup2(STDIN_FILENO, new_fd);
}

static void	search_redir_oper(char **cmd, char **env)
{
	char	**ptr;

	ptr = cmd;
	while (++ptr)
	{
		if (!ft_strncmp(*ptr, "<", ft_strlen(*ptr)))
			inp_oper(cmd, env);
		// else if (!ft_strncmp(*ptr, ">", ft_strlen(*ptr)))
		// 	out_oper();
		// else if (!ft_strncmp(*ptr, "<<", ft_strlen(*ptr)))
		// 	heredoc_oper();
		// else if (!ft_strncmp(*ptr, ">>", ft_strlen(*ptr)))
		// 	app_oper();
	}
}

int main(int argc, char **argv, char **env)
{
	char *cmd[5] = {"cat", "-e", "<", "main.c", NULL};

	(void)argc;
	(void)argv;
	search_redir_oper(cmd, env);
}

// cc redir_oper.c -o redir_oper commands.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c -Wall -Werror -Wextra