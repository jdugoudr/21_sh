/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 19:24:57 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/13 19:36:17 by mdaoud           ###   ########.fr       */
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
		ft_dprintf(STDOUT_FILENO, "%s\n", g_shell->env[i]);
		i++;
	}
	return (0);
}
