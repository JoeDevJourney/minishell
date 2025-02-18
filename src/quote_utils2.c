/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:59:52 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/18 17:09:17 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_quote_state	init_quote_state(void)
{
	t_quote_state	state;

	state.sq = false;
	state.dq = false;
	state.escape = false;
	return (state);
}
