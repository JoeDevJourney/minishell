/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:45:24 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/29 18:38:59 by dchrysov         ###   ########.fr       */
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

int		main(int argc, char **argv);
// int		exec_pipe(int num, char **cmd);
int		exec_pipe(char *cmds[], int num_cmds);
int		externals(char **str);
#endif