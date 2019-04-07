/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:26:12 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 18:31:01 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			display_history(t_shell *shell)
{
	int			i;
	t_history	*tmp;

	i = 1;
	tmp = shell->hist;
	while (tmp != NULL)
	{
		ft_printf("%d:  %s\n", i, tmp->name);
		tmp = tmp->next;
		i++;
	}
}
