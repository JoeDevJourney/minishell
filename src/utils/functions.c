/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:13:09 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/09 22:02:10 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Initializes redir struct variables
 */
void	init_redir(t_data *inp)
{
	inp->inp_op.cmd = NULL;
	inp->inp_op.fd = NULL;
	inp->inp_op.num_cmd = 0;
	inp->app_op.cmd = NULL;
	inp->app_op.fd = NULL;
	inp->app_op.num_cmd = 0;
	inp->out_op.cmd = NULL;
	inp->out_op.fd = NULL;
	inp->out_op.num_cmd = 0;
	inp->hdoc_op.cmd = NULL;
	inp->hdoc_op.fd = NULL;
	inp->hdoc_op.num_cmd = 0;
	inp->cmd = NULL;
	inp->tok = NULL;
	// errno = 0;
}

/**
 * @brief Joins 3 str together
 */
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

void	update_shell_lvl(t_data *inp)
{
	int		lvl;
	char	*shlvl_val;
	char	*lvl_str;

	lvl = 1;
	shlvl_val = get_env_val(inp->env, "SHLVL");
	if (shlvl_val)
		lvl = ft_atoi(shlvl_val) + 1;
	lvl_str = ft_itoa(lvl);
	if (lvl_str)
	{
		update_env_var(&inp->env, "SHLVL", lvl_str);
		free(lvl_str);
	}
}

char **list_to_array(t_env *head)
{
    int count = 0;
    t_env *temp = head;
    char **arr;
    int i = 0;

    while (temp)
    {
        count++;
        temp = temp->next;
    }
    arr = safe_malloc((count + 1) * sizeof(char *));
    while (head)
    {
        size_t len = strlen(head->name) + strlen(head->value) + 2;
        arr[i] = safe_malloc(len);
        if (!arr[i])
            return (free_array(arr), NULL);
        snprintf(arr[i], len, "%s=%s", head->name, head->value);
        i++;
        head = head->next;
    }
    arr[i] = NULL;
    return (arr);
}
