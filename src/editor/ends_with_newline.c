/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends_with_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:50:54 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 18:32:07 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

static void		get_pos(int *row, int *col)
{
	char	buf[30];
	int		i;
	int		pow_var;
	char	ch;

	*row = 0; *col = 0;
	ft_bzero(buf, 20);
	write(g_editor->tty_fd, "\033[6n", 4);
	for( i = 0, ch = 0; ch != 'R'; i++ )
	{
		read(STDIN_FILENO, &ch, 1);
		buf[i] = ch;
	}
	for (i -= 2, pow_var = 1; buf[i] != ';'; i--, pow_var *= 10)
		*col = *col + ( buf[i] - '0' ) * pow_var;
	for( i-- , pow_var = 1; buf[i] != '['; i--, pow_var *= 10)
		*row = *row + ( buf[i] - '0' ) * pow_var;
}

int				ends_with_newline(void)
{
	int	col;
	int	row;

	get_pos(&row, &col);
	return (col == 1);
}
