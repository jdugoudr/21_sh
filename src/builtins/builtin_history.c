/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:29:18 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/24 18:13:27 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			builtin_history(t_shell *shell)
{
	t_history	*hist;

	hist = shell->hist;
	while (hist != NULL)
	{
		ft_dprintf(g_editor->tty_fd, "%s", hist->name);
		hist = hist->next;
	}
}