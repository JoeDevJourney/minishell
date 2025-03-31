/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:12:47 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/31 21:57:20 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*build_prompt(t_data *inp)
{
	char	*prompt;
	char	*user;
	char	*pwd;
	char	*temp;

	temp = get_env_val(*inp, "USER");
	if (temp)
		user = temp;
	else
		user = ft_strdup("");
	prompt = ft_strjoin3(GRN, user, "@");
	free(user);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("/");
	prompt = ft_strjoin_free(&prompt, ft_strrchr(pwd, '/') + 1);
	prompt = ft_strjoin_free(&prompt, RST " % ");
	free(pwd);
	return (prompt);
}

bool	setup_heredoc_fd(t_data *inp, char **hdoc, size_t i)
{
	*hdoc = ft_strjoin(inp->home_dir, "/obj/heredoc");
	inp->hdoc_op.fd = safe_malloc(3 * sizeof(int *));
	inp->hdoc_op.fd[0] = safe_malloc(sizeof(int));
	*inp->hdoc_op.fd[0] = STDIN_FILENO;
	inp->hdoc_op.fd[1] = safe_malloc(sizeof(int));
	inp->hdoc_op.fd[2] = NULL;
	if (!inp->hdoc_op.cmd[i])
		return (printf("bash: syntax error near unexpected token `<<'\n"),
			inp->ret_val = 258, free_array_fd(inp->hdoc_op.fd),
			free(*hdoc), false);
	*inp->hdoc_op.fd[1] = open(*hdoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*inp->hdoc_op.fd[1] == -1)
		return (perror(inp->hdoc_op.cmd[i]),
			free_array_fd(inp->hdoc_op.fd), free(*hdoc), false);
	return (true);
}

void	exit_free(t_data *inp)
{
	free(inp->home_dir);
	free_env_list(inp->env);
	free_commands(inp);
	free_redir(inp);
}

void	find_dir_exec(const char *dirpath, const char *exec, char **path)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dirpath);
	if (!dir)
		return (perror(dirpath));
	entry = readdir(dir);
	while (entry)
	{
		if (!ft_strncmp(exec, entry->d_name, ft_strlen(exec))
			&& entry->d_name[ft_strlen(exec)] == '\0' && !*path)
			*path = ft_strdup(dirpath);
		entry = readdir(dir);
	}
	closedir(dir);
}

int	parse_n_flag(char **arr, bool *nl_flag)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i] && arr[i][0] == '-')
	{
		j = 1;
		while (arr[i][j] == 'n')
			j++;
		if (arr[i][j] != '\0')
			break ;
		i++;
		*nl_flag = false;
	}
	return (i);
}
