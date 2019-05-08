/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:37:29 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/24 18:11:15 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell21.h>
#include <stdlib.h>

void			free_shell(t_shell *sh)
{
	size_t		i;
	t_history	*tmp;

	if (sh->env != NULL)
	{
		i = 0;
		while (sh->env[i] != NULL)
		{
			free(sh->env[i]);
			i++;
		}
		free(sh->env);
	}
	while (sh->hist != NULL)
	{
		tmp = sh->hist->next;
		free(sh->hist);
		sh->hist = tmp;
	}
}
