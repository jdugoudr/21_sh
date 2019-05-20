/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:22:31 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 18:06:32 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			free_editor(void)
{
	if (g_editor != NULL)
	{
		if (g_editor->term != NULL)
			free(g_editor->term);
		if (g_editor->oldterm)
			free(g_editor->oldterm);
		free(g_editor);
	}
}
