/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:24:57 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 17:03:08 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

int	builtin_env(char **cmd)
{
	size_t		i;

	(void)cmd;
	i = 0;
	while (g_shell->env[i])
	{
		ft_printf("%s\n", g_shell->env[i]);
		i++;
	}
	return (0);
}
