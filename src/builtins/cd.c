/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/28 12:04:15 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Adds the new entry to the env list.
 */
static void	add_env_var(t_env **head, char *name, char *value)
{
	t_env	*current;

	current = (*head);
	while (current->next)
		current = current->next;
	current->next = safe_malloc(sizeof(t_env));
	current->next->name = ft_strdup(name);
	if (value)
		current->next->value = ft_strdup(value);
	else
		current->next->value = NULL;
	current->next->next = NULL;
}

static bool	replace_env_var(t_env **head, char *name, char *new_val)
{
	t_env	*current;

	current = *head;
	while (current)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(name))
			&& ft_strlen(name) == ft_strlen(current->name))
		{
			if (current->value)
				free(current->value);
			if (new_val)
				current->value = ft_strdup(new_val);
			else
				current->value = NULL;
			return (true);
		}
		current = current->next;
	}
	return (false);
}

/**
 * @brief Adds a new element in the env list if it doesn't already exist,
 * otherwise it replaces its value.
 */
int	update_env_var(t_env **head, char *name, char *value)
{
	if (!replace_env_var(head, name, value))
		add_env_var(head, name, value);
	return (0);
}

int	exec_cd(t_data *inp)
{
	char	*target_dir;
	char	*cwd;

	if (!get_env_val(*inp, "PWD") || !*get_env_val(*inp, "PWD")
		|| *get_env_val(*inp, "PWD") == ' ')
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (perror("getcwd failed"), 1);
	}
	update_env_var(&inp->env, "PWD", getcwd(NULL, 0));
	target_dir = get_target_dir(*inp);
	if (!target_dir || chdir(target_dir) != 0)
		return (perror(*inp->tok), 1);
	if (update_env_var(&inp->env, "OLDPWD", get_env_val(*inp, "PWD")) != 0)
		return (perror("Error updating OLDPWD"), 1);
	free(target_dir);
	target_dir = getcwd(NULL, 0);
	if (update_env_var(&inp->env, "PWD", target_dir) != 0)
		return (perror("Error updating $PWD"), 1);
	free(target_dir);
	free(cwd);
	return (0);
}
