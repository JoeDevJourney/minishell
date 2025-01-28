/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:45:24 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/28 15:11:09 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft/include/libft.h"

int			ft_strcmp(char *s1, char *s2);
void		exit_handler(int n_exit);
int			open_file(char *file, int in_or_out);
void		free_tab(char **tab);
char		*own_getenv(char *name, char **env);
char		*find_path(char **allpath, char *cmd);
char		*get_path(char *cmd, char **env);
void		exec(char *cmd, char **env);
void		child(char *argv, int *p_fd);
void		parent(char *argv, int *p_fd);
int			main(int argc, char **argv, char **env);
void		create_child_process(char **argv, int *p_fd);
void		externals(char **str);
#endif