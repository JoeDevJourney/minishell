/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:45:24 by jbrandt           #+#    #+#             */
/*   Updated: 2025/01/30 16:17:07 by dchrysov         ###   ########.fr       */
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
# include <errno.h>

int		main(int argc, char **argv);
int		exec_pipes(int num, char **cmd);
int		externals(char **str);
void	*safe_malloc(size_t size);

#endif