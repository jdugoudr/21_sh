/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends_with_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:50:54 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/09 16:45:47 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <termios.h>

static void		get_pos(int *row, int *col)
{
	char	buf[30];
	int		i;
	int		pow;
	char	ch;

	*row = 0; *col = 0;
	ft_bzero(buf, 20);
	write(1, "\033[6n", 4);
	for( i = 0, ch = 0; ch != 'R'; i++ )
	{
		read(0, &ch, 1);
		buf[i] = ch;
	}
	for (i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
		*col = *col + ( buf[i] - '0' ) * pow;
	for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
		*row = *row + ( buf[i] - '0' ) * pow;
}

int				ends_with_newline(void)
{
	int	col;
	int	row;

	get_pos(&row, &col);
	return (col == 1);
}
