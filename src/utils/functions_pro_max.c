/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_pro_max.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:35:31 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/29 20:45:07 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_oldpwd_dir(t_data inp)
{
	char	*oldpwd;

	oldpwd = get_env_val(inp, "OLDPWD");
	if (!oldpwd)
		printf("bash: cd: OLDPWD not set\n");
	return (oldpwd);
}

static char	*process_argument(t_data inp)
{
	char	*trimmed;
	char	*res;
	char	*pwd;

	if (!ft_strncmp(inp.tok[1], "-", 1) && ft_strlen(inp.tok[1]) == 1)
	{
		pwd = get_oldpwd_dir(inp);
		if (!pwd)
			return (free(pwd), NULL);
		return (printf("%s\n", pwd), pwd);
	}
	if (inp.tok[1][0] == '~')
		return (ft_strjoin3(inp.home_dir, "/", inp.tok[1] + 1));
	if (inp.tok[1][0] == '\0')
		return (NULL);
	if (inp.tok[1][0] == '/')
		return (ft_strdup(inp.tok[1]));
	trimmed = ft_strtrim(inp.tok[1], "/");
	pwd = get_env_val(inp, "PWD");
	if (!pwd)
		pwd = ft_strdup("");
	res = ft_strjoin3(pwd, "/", trimmed);
	return (free(trimmed), free(pwd), res);
}

char	*get_target_dir(t_data inp)
{
	char	*home;

	if (!inp.tok[1])
	{
		home = get_env_val(inp, "HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			home = "";
		}
		return (home);
	}
	return (process_argument(inp));
}

/**
 * @brief Expands all redir operators, keeping any quotes, except for the hdoc
 * 
 * @note The fds won't be tokenized, cause it messes with their execution.
 * Instead they are trimmed for both single and double quotes.
 * Hdoc is handled speacially.
 */
void	expand_redir(t_data *inp)
{
	int		arr_i;
	int		str_i;
	char	*trimmed;
	char	**arr[4];

	arr[0] = inp->inp_op.cmd;
	arr[1] = inp->out_op.cmd;
	arr[2] = inp->app_op.cmd;
	arr[3] = NULL;
	arr_i = -1;
	while (arr[++arr_i])
	{
		str_i = -1;
		while (arr[arr_i][++str_i])
		{
			expansion(&arr[arr_i][str_i], *inp);
			trimmed = ft_strtrim(arr[arr_i][str_i], "\"");
			free(arr[arr_i][str_i]);
			arr[arr_i][str_i] = trimmed;
			trimmed = ft_strtrim(arr[arr_i][str_i], "'");
			free(arr[arr_i][str_i]);
			arr[arr_i][str_i] = trimmed;
		}
	}
}
