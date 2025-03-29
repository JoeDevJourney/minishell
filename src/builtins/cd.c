/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/03/29 20:48:01 by jbrandt          ###   ########.fr       */
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
	current->next->value = ft_strdup(value);
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
			free(current->value);
			current->value = ft_strdup(new_val);
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
	char	*pwd;

	target_dir = getcwd(NULL, 0);
	pwd = get_env_val(*inp, "PWD");
	if (!pwd || !*pwd || *pwd == ' ')
		update_env_var(&inp->env, "PWD", target_dir);
	free(target_dir);
	target_dir = get_target_dir(*inp);
	if (!target_dir)
		return (free(target_dir), free(pwd), 1);
	if (chdir(target_dir) != 0)
		return (perror(*inp->tok), free(target_dir), free(pwd), 1);
	if (update_env_var(&inp->env, "OLDPWD", pwd) != 0)
		return (printf("Error with OLDPWD"), free(target_dir), free(pwd), 1);
	free(target_dir);
	target_dir = getcwd(NULL, 0);
	if (update_env_var(&inp->env, "PWD", target_dir) != 0)
		return (printf("Error with $PWD"), free(target_dir), free(pwd), 1);
	printf("%s \n %s", pwd, target_dir);
	free(target_dir);
	free(pwd);
	return (0);
}
