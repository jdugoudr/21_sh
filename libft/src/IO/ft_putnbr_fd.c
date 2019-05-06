/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 18:52:28 by mdaoud            #+#    #+#             */
/*   Updated: 2018/11/17 15:16:24 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(int num, int fd)
{
	if (num == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (1);
	}
	if (num == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	return (0);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		buff[15];
	int		i;

	if (ft_check(n, fd))
		return ;
	i = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	while (n)
	{
		buff[i++] = n % 10;
		n /= 10;
	}
	while (--i >= 0)
		ft_putchar_fd(buff[i] + '0', fd);
}
