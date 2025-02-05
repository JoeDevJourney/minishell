/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/05 13:28:48 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	*inp_oper(char **cmd, t_data *inp)
{
	int		*fd;
	char	*temp;
	char	*filename;
	char	**ptr;

	fd = NULL;
	temp = join_cmd(cmd);
	ptr = ft_split(temp, '<');
	filename = ft_strjoin(ptr[0], ptr[str_count(temp, '<') - 1]);
	inp->redir.cmd = ft_split(filename, ' ');
	inp->redir.num_cmd = str_count(filename, ' ');
	fd = safe_malloc(2 * sizeof(int));
	fd[0] = open(inp->redir.cmd[inp->redir.num_cmd - 1], O_RDONLY);
	if (fd[0] == -1)
		return (perror("Error opening the file"), &errno);
	fd[1] = STDIN_FILENO;
	dup2(fd[0], fd[1]);
	return (free(filename), free_array(ptr), free(temp), fd);
}

static char	**dupl_arr(char **arr)
{
	char	**new_arr;
	int		i;
	int		count;

	count = 0;
	while (arr[count])
		count++;
	new_arr = safe_malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		new_arr[i] = strdup(arr[i]);
		if (!new_arr[i])
		{
			while (--i >= 0)
				free(new_arr[i]);
			free(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

int	*search_redir_oper(char **cmd, t_data *inp)
{
	char	**ptr;
	int		*fd;

	ptr = cmd;
	fd = NULL;
	while (*++ptr)
	{
		if (!ft_strncmp(*ptr, "<", ft_strlen(*ptr)))
		{
			fd = inp_oper(cmd, inp);
			break ;
		}
		// }
		// else if (!ft_strncmp(*ptr, ">", ft_strlen(*ptr)))
		// 	out_oper();
		// else if (!ft_strncmp(*ptr, "<<", ft_strlen(*ptr)))
		// 	heredoc_oper();
		// else if (!ft_strncmp(*ptr, ">>", ft_strlen(*ptr)))
		// 	app_oper();
		else
			inp->redir.cmd = dupl_arr(cmd);
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