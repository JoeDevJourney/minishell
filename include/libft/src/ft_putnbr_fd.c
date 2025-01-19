/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/12 14:12:17 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_div(int num)
{
	int	res;
	int	i;

	res = 1;
	i = 1;
	while (i <= num / 10)
	{
		res *= 10;
		i *= 10;
	}
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	num;
	int		div;
	int		digit;

	if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n *= -1;
		}
		div = ft_div(n);
		while (div > 0)
		{
			digit = n / div;
			num = digit + '0';
			write(fd, &num, 1);
			n %= div;
			div /= 10;
		}
	}
}
