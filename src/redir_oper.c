/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/05 20:04:04 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	*out_oper(t_data *inp)
{
	int		*fd;
	char	**tok;
	int		i;

	tok = ft_split(*inp->pipe.cmd, '>');
	inp->redir.cmd = ft_split(*tok, ' ');
	inp->redir.num_cmd = str_count(*tok, ' ');
	fd = safe_malloc(str_count(*inp->pipe.cmd, '>') * sizeof(int));
	i = -1;
	while (++i < (int)str_count(*inp->pipe.cmd, '>') - 1)
	{
		fd[i] = open(ft_strtrim(tok[i + 1], " "),
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[i] == -1)
			return (perror("Error opening the file"), &errno);
		if (i < (int)str_count(*inp->pipe.cmd, '>') - 2)
			close(fd[i]);
	}
	fd[i] = STDOUT_FILENO;
	dup2(fd[i - 1], fd[i]);
	return (free_array(tok), fd);
}

static int	*inp_oper(t_data *inp)
{
	int		*fd;
	char	**ptr;

	ptr = ft_split(*inp->pipe.cmd, '<');
	inp->redir.cmd = ft_split(*ptr, ' ');
	inp->redir.num_cmd = str_count(*ptr, ' ');
	fd = safe_malloc(2 * sizeof(int));
	fd[0] = open(ft_strtrim(ptr[str_count(*inp->pipe.cmd, '<') - 1], " "), O_RDONLY);
	if (fd[0] == -1)
		return (perror("Error opening the file"), &errno);
	fd[1] = STDIN_FILENO;
	dup2(fd[0], fd[1]);
	return (free_array(ptr), fd);
}

int	*search_redir_oper(t_data *inp)
{
	int		*fd;

	if (ft_strnstr(*inp->pipe.cmd, "<", ft_strlen(*inp->pipe.cmd)))
		fd = inp_oper(inp);
	else if (ft_strnstr(*inp->pipe.cmd, ">", ft_strlen(*inp->pipe.cmd)))
		fd = out_oper(inp);
	// else if (!ft_strncmp(*ptr, "<<", ft_strlen(*ptr)))
	// 	heredoc_oper();
	// else if (!ft_strncmp(*ptr, ">>", ft_strlen(*ptr)))
	// 	app_oper();
	else
	{
		fd = NULL;
		inp->redir.cmd = ft_split(*inp->pipe.cmd, ' ');
		inp->redir.num_cmd = str_count(*inp->pipe.cmd, ' ');
	}
	return (fd);
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