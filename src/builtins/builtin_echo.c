/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 02:48:47 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/28 16:15:47 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"

/*
** Handles the echo command when the "-n" option is specified.
** -n: do not output the trailing newline character.
*/

static int		echo_with_no_newline(char **cmd)
{
	size_t		i;

	if (cmd[2] == NULL)
		return (0);
	i = 2;
	while (cmd[i] != NULL)
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	return (0);
}

int				builtin_echo(char **cmd)
{
	size_t	i;

	if (cmd[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else if (ft_strequ("-n", cmd[1]))
		return (echo_with_no_newline(cmd));
	i = 1;
	while (cmd[i] != NULL)
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
