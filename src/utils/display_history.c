/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:26:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/08 19:17:40 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			display_history(void)
{
	int			i;
	t_history	*tmp;

	i = 1;
	tmp = g_shell->hist;
	while (tmp != NULL)
	{
		dprintf(STDOUT_FILENO, "%d: %s\n", i, tmp->name);
		tmp = tmp->next;
		i++;
	}
}
