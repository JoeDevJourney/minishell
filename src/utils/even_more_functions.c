/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/14 14:31:57 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	count_array_size(char **arr)
{
	size_t	len;

	len = 0;
	while (arr && arr[len])
		len++;
	return (len);
}
