/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:24:57 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/28 16:15:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"

int	builtin_env(char **cmd)
{
	size_t		i;

	(void)cmd;
	i = 0;
	while (g_shell->env[i])
	{
		write(STDOUT_FILENO, g_shell->env[i], ft_strlen(g_shell->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
