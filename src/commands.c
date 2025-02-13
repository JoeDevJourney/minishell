/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:42:19 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/13 20:57:41 by dchrysov         ###   ########.fr       */
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

void	exec_external(t_data inp)
{
	char	*dir;
	char	*full_path;

	dir = ft_strjoin(path_to_exec(*inp.command), "/");
	full_path = ft_strjoin(dir, *inp.command);
	free(*inp.command);
	*inp.command = ft_strdup(full_path);
	free(full_path);
	free(dir);
	if (execve(*inp.command, inp.command, inp.env) == -1)
		exit_with_error(*inp.command, errno);
}

/**
 * @brief Creates the child process for a single command
 */
int	fork_command(t_data *inp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exec_external(*inp);
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

/**
 * @brief Handles all execution, both externals and builtins
 */
void	handle_command(t_data *inp)
{
	int	fd;
	int	sstdin;

	fd = -1;
	sstdin = dup(STDIN_FILENO);
	// search_redir_oper(inp, &fd);
	if (inp->pipe.num_cmd != 1)
		inp->ret_val = handle_pipes(inp);
	else
		if (!search_builtins(*inp))
			inp->ret_val = fork_command(inp);
	if (fd != -1)
	{
		dup2(sstdin, STDIN_FILENO);
		close(fd);
	}
	close(sstdin);
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
// 	inp.pipe.cmd[0] = ft_strdup("cat -e < ../Makefile");
// 	inp.pipe.cmd[1] = NULL;
// }
// cc commands.c -o commands redirection.c pipex.c utils/parsing.c ../include/libft/src/ft_strncmp.c ../include/libft/src/ft_strlen.c ../include/libft/src/ft_strdup.c ../include/libft/src/ft_strjoin.c utils/functions.c ../include/libft/src/ft_memmove.c builtins/builtins.c ../include/libft/src/ft_split.c ../include/libft/src/ft_strlcat.c ../include/libft/src/ft_strchr.c ../include/libft/src/ft_strlcpy.c builtins/env.c builtins/pwd.c ../include/libft/src/ft_putendl_fd.c ../include/libft/src/ft_strnstr.c ../include/libft/src/ft_strtrim.c utils/more_functions.c -Wall -Werror -Wextra -g -lreadline 

	// printf("pipes: [");
	// while (inp.pipe.cmd && *inp.pipe.cmd)
	// 	printf("'%s', ", *inp.pipe.cmd++);
	// printf("]\n");
	// printf("inp: [");
	// while (inp.inp_op.cmd && *inp.inp_op.cmd)
	// 	printf("'%s', ", *inp.inp_op.cmd++);
	// printf("]\n");
	// printf("out: [");
	// while (inp.out_op.cmd && *inp.out_op.cmd)
	// 	printf("'%s', ", *inp.out_op.cmd++);
	// printf("]\n");
	// printf("app: [");
	// while (inp.app_op.cmd && *inp.app_op.cmd)
	// 	printf("'%s', ", *inp.app_op.cmd++);
	// printf("]\n");
	// printf("hdoc: [");
	// if (!inp.hdoc_op.cmd)
	// 	printf("(null)\n");
	// printf("]\n");