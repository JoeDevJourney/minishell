/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/12 16:56:51 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*path_to_exec(char *name)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**path;
	char			**ptr;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (perror("$PATH not set"), NULL);
	ptr = path;
	while (*ptr)
	{
		dir = opendir(*ptr);
		if (!dir)
			return (perror(*ptr), NULL);
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strncmp(name, entry->d_name, ft_strlen(entry->d_name)))
				return (closedir(dir), *ptr);
			entry = readdir(dir);
		}
		closedir (dir);
		ptr++;
	}
	free_array(path);
	perror(name);
	exit(127);
}

static void	exec_external(t_data inp)
{
	char	*dir;
	char	*full_path;

	// expansion_oper(argv);
	dir = ft_strjoin(path_to_exec(*inp.redir.cmd), "/");
	full_path = ft_strjoin(dir, *inp.redir.cmd);
	free(*inp.redir.cmd);
	*inp.redir.cmd = ft_strdup(full_path);
	free(full_path);
	free(dir);
	if (execve(*inp.redir.cmd, inp.redir.cmd, inp.env) == -1)
		exit_with_error(*inp.redir.cmd, errno);
}

/**
 * @brief Handles all execution, both externals and builtins
 */
void	exec_command(t_data *inp)
{
	// input = join_cmd(str);				//
	// cmd = ft_split(input, ' ');			// TODO: double quotes handling
	search_redir_oper(inp);
	if (!search_builtins(*inp))
		exec_external(*inp);
}

/**
 * @brief Creates the child process for a single command
 */
int	handle_command(t_data *inp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exec_command(inp);
		exit(1);
	}
	else if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
		// if (unlink(ft_strjoin(inp.home_dir, "/src/heredoc")) == -1)
		// 	printf("wrong\n");
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	else
		perror("Fork failed");
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_data	inp;

// 	(void)argc;
// 	(void)argv;
// 	inp.env = env;
// 	inp.home_dir = getenv("PWD");
// 	inp.and.cmd = NULL;
// 	inp.or.cmd = NULL;
// 	inp.pipe.cmd = safe_malloc(2 * sizeof(char *));
// 	inp.pipe.cmd[0] = ft_strdup("env");
// 	inp.pipe.cmd[1] = NULL;
// 	exec_command(&inp);
// 	// handle_command(&inp);
// 	free_input(&inp);
// }
// cc commands.c -o commands redirection.c utils/parsing.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c utils/functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c ../include/libft/src/ft_putendl_fd.c ../include/libft/src/ft_strnstr.c ../include/libft/src/ft_strtrim.c utils/more_functions.c -Wall -Werror -Wextra -g -lreadline
