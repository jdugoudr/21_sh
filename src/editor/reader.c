/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 15:32:33 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/20 15:03:28 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"
#include "keypress.h"
#include "shell21.h"
#include <stdint.h>

static long		delete_key(void)
{
	unsigned char	buf;

	if ((read(STDIN_FILENO, &buf, 1)) < 0)
		return (-1);
	return (buf << 24 | '3' << 16 | '[' << 8 | 0x1B);
}

static long		shift_arrow(void)
{
	unsigned char	buf;
	long			tmp;
	long			result;

	tmp = 0x32L << 32;
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
			result = (0x0L | buf) << 40;
			result = result | tmp | ';' << 24 | '1' << 16 | '[' << 8 | 0x1B;
			return (result);
		}
		result = (0x0L | buf) << 32 | ';' << 24 | '1' << 16 | '[' << 8 | 0x1B;
	}
	result = buf << 24 | '1' << 16 | '[' << 8 | 0x1B;
	return (result);
}

static long		dispatch_esc_seq(void)
{
	unsigned char	buf;
	int				ret;

	if ((ret = read(STDIN_FILENO, &buf, 1)) < 0)
		return (-1);
	if (buf != '1' && buf != '3')
		return (buf << 16 | '[' << 8 | 0x1B);
	else if (buf == '3')
		return (delete_key());
	else if (buf == '1')
		return (shift_arrow());
	return (buf << 16 | '[' << 8 | 0x1B);
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
