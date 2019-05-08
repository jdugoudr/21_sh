/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:37:29 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/08 19:18:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <stdlib.h>

void			free_shell(void)
{
	size_t		i;
	t_history	*tmp;

	if (g_shell->env != NULL)
	{
		i = 0;
		while (g_shell->env[i] != NULL)
		{
			free(g_shell->env[i]);
			i++;
		}
		free(g_shell->env);
	}
	while (g_shell->hist != NULL)
	{
		tmp = g_shell->hist->next;
		free(g_shell->hist);
		g_shell->hist = tmp;
	}
}
