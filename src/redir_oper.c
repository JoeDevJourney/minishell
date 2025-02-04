/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/04 13:53:16 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	rm_redir_oper(char **arr, char *oper)
{
	int	read;
	int	write;

	read = 0;
	write = 0;
	if (!arr || !oper)
		return ;
	while (arr[read] != NULL)
	{
		if (strcmp(arr[read], oper) == 0)
		{
			free(arr[read]);
			arr[read] = NULL;
		}
		else
		{
			arr[write] = arr[read];
			write++;
		}
		read++;
	}
	arr[write] = NULL;
}

static int	*inp_oper(char **cmd)
{
	int		*fd;
	char	*filename;
	char	**ptr;

	filename = join_cmd(cmd);
	ptr = ft_split(filename, '<');
	free(filename);
	filename = ft_strdup(ptr[1]);
	rm_redir_oper(cmd, "<");
	fd = safe_malloc(2 * sizeof(int));
	fd[0] = open(filename, O_RDONLY);
	if (fd[0] == -1)
		return (perror("Error opening the file"), &errno);
	fd[1] = STDIN_FILENO;
	dup2(fd[0], fd[1]);
	free(ptr);
	return (fd);
}

int	*search_redir_oper(char **cmd)
{
	char	**ptr;
	int		*fd;

	ptr = cmd;
	fd = NULL;
	while (*++ptr)
	{
		if (!ft_strncmp(*ptr, "<", ft_strlen(*ptr)))
			fd = inp_oper(cmd);
		// else if (!ft_strncmp(*ptr, ">", ft_strlen(*ptr)))
		// 	out_oper();
		// else if (!ft_strncmp(*ptr, "<<", ft_strlen(*ptr)))
		// 	heredoc_oper();
		// else if (!ft_strncmp(*ptr, ">>", ft_strlen(*ptr)))
		// 	app_oper();
	}
	return (fd);			// (??????)
}

// int	main(int argc, char **argv, char **env)
	// {
	// 	char	**cmd;
	//
	// 	(void)argc;
	// 	(void)argv;
	// 	cmd = malloc(5 * sizeof(char *));
	// 	cmd[0] = ft_strdup("cat");
	// 	cmd[1] = ft_strdup("-e");
	// 	cmd[2] = ft_strdup("<");
	// 	cmd[3] = ft_strdup("parsing.c");
	// 	cmd[4] = NULL;
	// 	search_redir_oper(cmd, env);
	// }

// cc redir_oper.c -o redir_oper commands.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c -Wall -Werror -Wextra