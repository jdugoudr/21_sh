/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:29:18 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/13 17:48:18 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"

int			builtin_history(char **cmd)
{
	t_history	*hist;

	(void)cmd;
	hist = g_shell->hist;
	while (hist != NULL)
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", hist->name);
		hist = hist->next;
	}
	return (0);
}
