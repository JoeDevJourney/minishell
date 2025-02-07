/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/07 14:01:37 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @note **path needs freeing!(?)  <---------------
 */
static char	*path_to_exec(char *name)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**path;

	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (printf("$PATH not set\n"), NULL);
	while (*path)
	{
		dir = opendir(*path);
		if (!dir)
			return (perror("opendir failed"), NULL);
		entry = readdir(dir);
		while (entry)
		{
			if (!ft_strncmp(name, entry->d_name, ft_strlen(entry->d_name)))
				return (closedir(dir), *path);
			entry = readdir(dir);
		}
		closedir (dir);
		path++;
	}
	perror(name);
	exit(errno);
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
	{
		perror(*inp.redir.cmd);
		exit(errno);
	}
}

/**
 * @brief Handles all execution, both externals and builtins
 */
void	exec_command(t_data inp)
{
	// input = join_cmd(str);				//
	// cmd = ft_split(input, ' ');			// TODO: double quotes handling
	search_redir_oper(&inp);
	search_builtins(inp);
	exec_external(inp);
	// free_array(inp.redir.cmd);		// for custom main freeing
	exit(1);
}

/**
 * @brief Creates the child process for a single command
 */
int	handle_command(t_data inp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_command(inp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
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
// 	inp.home_dir = ft_strjoin(getenv("PWD"), "/..");
// 	inp.pipe.cmd = malloc(2 * sizeof(char *));
// 	if (!inp.pipe.cmd)
// 		return (0);
// 	inp.pipe.cmd[0] = ft_strdup("cat < main.c");
// 	inp.pipe.cmd[1] = NULL;
// 	// exec_command(inp);
// 	handle_command(inp);
// 	// printf("ret: %d\n", handle_command(inp));
// 	free_array(inp.pipe.cmd);
// 	free(inp.home_dir);
// }
// cc commands.c -o commands functions.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcpy.c ../include/libft/src/ft_strjoin.c ../include/libft/src/ft_strlcat.c redir_oper.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_memmove.c ../include/libft/src/ft_strtrim.c builtins/*.c ../include/libft/src/ft_strnstr.c -g -Wall -Werror -Wextra
