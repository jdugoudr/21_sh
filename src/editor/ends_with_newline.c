/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends_with_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:50:54 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:05:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

static void		init_vars(int *col, int *row, char buf[])
{
	*row = 0;
	*col = 0;
	ft_bzero(buf, 30);
}

static void		read_loop(char buf[], int *i)
{
	char	ch;

	*i = 0;
	ch = 0;
	while (ch != 'R')
	{
		read(STDIN_FILENO, &ch, 1);
		buf[*i] = ch;
		(*i)++;
	}
}

static void		get_pos(int *row, int *col)
{
	char	buf[30];
	int		i;
	int		pow_var;

	init_vars(row, col, buf);
	write(g_editor->tty_fd, "\033[6n", 4);
	read_loop(buf, &i);
	i -= 2;
	pow_var = 1;
	while (buf[i] != ';')
	{
		*col = *col + (buf[i] - '0') * pow_var;
		i--;
		pow_var *= 10;
	}
	i--;
	pow_var = 1;
	while (buf[i] != '[')
	{
		*row = *row + (buf[i] - '0') * pow_var;
		i--;
		pow_var *= 10;
	}
}

int				ends_with_newline(void)
{
	int	col;
	int	row;

	get_pos(&row, &col);
	return (col == 1);
}
