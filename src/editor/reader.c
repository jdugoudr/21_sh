/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:32:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/31 18:43:26 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include "keypress.h"
#include "shell21.h"

static long		arrow_key(unsigned char buf)
{
	if (buf == 'A')
		return (UP_KEY);
	if (buf == 'B')
		return (DOWN_KEY);
	if (buf == 'C')
		return (RIGHT_KEY);
	if (buf == 'D')
		return (LEFT_KEY);
	return (0);
}

static long		delete_key(void)
{
	unsigned char	buf;

	if ((read(STDIN_FILENO, &buf, 1)) < 0)
		return (-1);
	if (buf == '~')
		return (DEL_KEY);
	return (0);
}

static long		shift_arrow(void)
{
	unsigned char	buf;

	if ((read(STDIN_FILENO, &buf, 1)) < 0)
		return (-1);
	if (buf == ';')
	{
		if ((read(STDIN_FILENO, &buf, 1)) < 0)
			return (-1);
		if (buf == '2')
		{
			if ((read(STDIN_FILENO, &buf, 1)) < 0)
				return (-1);
			if (buf == 'A')
				return (SHIFT_UP_KEY);
			if (buf == 'B')
				return (SHIFT_DOWN_KEY);
			if (buf == 'C')
				return (SHIFT_RIGHT_KEY);
			if (buf == 'D')
				return (SHIFT_LEFT_KEY);
		}
	}
	return (0);
}

static long		dispatch_esc_seq(void)
{
	unsigned char	buf;
	int				ret;

	if ((ret = read(STDIN_FILENO, &buf, 1)) < 0)
		return (-1);
	if (buf >= 'A' && buf <= 'D')
		return (arrow_key(buf));
	else if (buf == 'H')
		return (HOME_KEY);
	else if (buf == 'F')
		return (END_KEY);
	else if (buf == '3')
		return (delete_key());
	else if (buf == '1')
		return (shift_arrow());
	return (0);
}

long			reader(void)
{
	int				ret;
	unsigned char	buf;

	while ((ret = read(STDIN_FILENO, &buf, 1)))
	{
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (0);
		if (buf == 0x1B)
		{
			if ((ret = read(STDIN_FILENO, &buf, 1)) < 0)
				return (-1);
			else if (buf == '[')
				return (dispatch_esc_seq());
		}
		return (buf);
	}
	return (0);
}

// long		reader(void)
// {
// 	int		ret;
// 	char	buf[3];

// 	while ((ret = read(STDIN_FILENO, buf, 2)))
// 	{
// 		if (ret < 0)
// 			return (-1);
// 		if (ret == 0)
// 			return (0);
// 		if (buf[0] == ESC_KEY && buf[1] == '\0')
// 			return (ESC_KEY);
// 		else if (buf[0] == ESC_KEY && buf[1] == '[')
// 			return (dispatch_esc_seq());
// 		else
// 			return (buf[0]);
// 	}
// 	return (0);
// }
