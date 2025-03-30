/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:39:12 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/30 18:38:19 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	wait_n_free(t_data *inp)
{
	int	status;
	int	i;

	i = -1;
	while (++i < inp->pipe.num_cmd)
		if (wait(&status) == -1)
			exit_with_error("Child process failed", EXIT_FAILURE);
	free_array_fd(inp->pipe.fd);
	setup_signals(false);
	return (handle_signal_status(status));
}

static void	init_pipes(t_redir_op *oper)
{
	int	i;

	oper->fd = safe_malloc((oper->num_cmd + 1) * sizeof(int *));
	i = 0;
	oper->fd[i] = safe_malloc(2 * sizeof(int));
	oper->fd[i][0] = STDIN_FILENO;
	oper->fd[i][1] = STDOUT_FILENO;
	while (++i < oper->num_cmd)
	{
		oper->fd[i] = safe_malloc(2 * sizeof(int));
		if (pipe(oper->fd[i]) == -1)
		{
			while (--i >= 0)
			{
				close(oper->fd[i][0]);
				close(oper->fd[i][1]);
				free(oper->fd[i]);
			}
			free(oper->fd);
			exit_with_error("Pipe creation failed", EXIT_FAILURE);
		}
	}
	oper->fd[i] = NULL;
}

/**
 * @brief Redirection of the pipes' fds
 */
static void	process_pipe_fds(t_data *inp, int *old_fd, int *new_fd)
{
	char	**env;

	env = list_to_array(inp->env);
	if (*new_fd == STDOUT_FILENO)
	{
		dup2(old_fd[1], *new_fd);
		close (old_fd[1]);
	}
	else if (*new_fd == STDIN_FILENO)
	{
		dup2(old_fd[0], *new_fd);
		close (old_fd[1]);
	}
	else
	{
		close(new_fd[0]);
		dup2(old_fd[0], STDIN_FILENO);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
	close(old_fd[0]);
	inp->ret_val = exec_command(inp, true, env);
	free_array(&env, count_array_size(env));
}

/**
 * @brief Creates the child process for executing the command and makes
 * the parent wait for it to finish, before returning its value
 */
static int	fork_pipe(t_data *inp, int *old_fd, int *new_fd)
{
	int	pid;

	pid = fork();
	setup_signals(true);
	if (pid == 0)
	{
		if (!parse_input(inp) || !process_fds(inp) || !*inp->tok)
		{
			free_redir(inp);
			free(inp->input);
			free(inp->cmd);
			free(inp->home_dir);
			free_array(&inp->tok, count_array_size(inp->tok));
			free_env_list(inp->env);
			free_array_fd(inp->pipe.fd);
			free_array(&inp->pipe.cmd, inp->pipe.num_cmd);
			exit(1);
		}
		process_pipe_fds(inp, old_fd, new_fd);

		free_redir(inp);
		free(inp->input);
		free(inp->cmd);
		free(inp->home_dir);
		free_array(&inp->tok, count_array_size(inp->tok));
		free_env_list(inp->env);
		if (inp->pipe.cmd)
			free_array(&inp->pipe.cmd, inp->pipe.num_cmd);
		free_array_fd(inp->pipe.fd);
		exit(inp->ret_val);
	}
	return (pid);
}

/**
 * @brief Executes pipe(s) given in (char **) cmds.
 */
int	exec_pipes(t_data *inp)
{
	t_data	ptr;
	int		i;

	init_pipes(&inp->pipe);
	ptr = *inp;
	i = 0;
	fork_pipe(&ptr, ptr.pipe.fd[i + 1], &ptr.pipe.fd[0][1]);
	while (++i < ptr.pipe.num_cmd)
	{
		close(ptr.pipe.fd[i][1]);
		ptr.pipe.cmd++;
		if (i != ptr.pipe.num_cmd - 1)
			fork_pipe(&ptr, ptr.pipe.fd[i], ptr.pipe.fd[i + 1]);
		else
			fork_pipe(&ptr, ptr.pipe.fd[i], &ptr.pipe.fd[0][0]);
		close(ptr.pipe.fd[i][0]);
	}
	return (wait_n_free(&ptr));
}
