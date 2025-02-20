/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:37:31 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/20 19:28:17 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Removes the index line from the array and updates its size.
 */
static void	remove_line(char ***env, int index)
{
	char	**new_arr;
	int		size;
	int		i;
	int		j;

	size = count_array_size(*env);
	if (index < 0 || index >= size)
		return ;
	new_arr = safe_malloc(size * sizeof(char *));
	free((*env)[index]);
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (i != index)
		{
			new_arr[j] = (*env)[i];
			j++;
		}
	}
	new_arr[j] = NULL;
	free(*env);
	*env = new_arr;
}

/**
 * @brief Searches for *cmd in the **env
 * 
 * @returns The index of the variable found in **env (-1 if not found) 
 */
static int	var_index(char *cmd, char **env)
{
	char	**tok;
	int		len;
	int		i;

	i = -1;
	while (env[++i])
	{
		tok = ft_split(env[i], '=');
		len = ft_strlen(cmd);
		if (!ft_strncmp(cmd, *tok, len) && tok[0][len] == '\0')
			return (free_array(tok), i);
		free_array(tok);
	}
	return (-1);
}

// int	exec_unset(t_data *inp)
int	exec_unset(char **cmd, char ***env)
{
	int		index;

	if (!*cmd)
		return (0);
	if (!ft_strncmp(*cmd, "-v", ft_strlen(*cmd)) && ft_strlen(*cmd) == 2)
	{
		if (!*(cmd + 1))
			return (0);
		cmd++;
		while (*cmd)
		{
			index = var_index(*cmd, *env);
			remove_line(env, index);
			cmd++;
		}
		return (0);
	}
	return (printf("bash: unset: %s: invalid option\n", *cmd), 2);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_data	inp;
// 	int	i = -1;

// 	(void)argc;
// 	argv++;
// 	dupl_env(&inp.env, env);
// 	i = -1;
// 	printf("\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
// 	while (inp.env[++i])
// 		printf("inp.env[%d]: '%s'\n", i, inp.env[i]);
// 	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
// 	if (argc > 1)
// 		exec_unset(++argv, &inp.env);
// 	i = -1;
// 	printf("\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
// 	while (inp.env[++i])
// 		printf("inp.env[%d]: '%s'\n", i, inp.env[i]);
// 	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
// }
// cc unset.c env.c ../utils/more_functions.c ../utils/functions.c ../utils/even_more_functions.c ../../include/libft/src/ft_split.c ../../include/libft/src/ft_strdup.c ../../include/libft/src/ft_strlcpy.c ../../include/libft/src/ft_strlen.c ../../include/libft/src/ft_strncmp.c ../../include/libft/src/ft_strnstr.c ../../include/libft/src/ft_strchr.c -o unset -g -Wall -Werror -Wextra


// argv = 'unset'


// argv = 'unset' 'VAR'
// argv = 'unset' 'VAR1' 'VAR2' 'VAR3'


// argv = 'unset' '-v'
// argv = 'unset' '-v' 'VAR'
// argv = 'unset' '-v' 'VAR1' 'VAR2' 'VAR3'