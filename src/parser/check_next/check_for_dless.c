/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_dless.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:37:52 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/24 09:30:50 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"
#include "sh_error.h"
#include "ast.h"
#include "libft.h"
#include "editor.h"

/*
** We read on std_in until next->value are found.
** The new line is stock in next->value
*/

int			check_for_dless(t_ast *next, char **line)
{
	char	*new;

	(void)line;
	if ((next->type & AFTER_DLESS) == 0)
	{
		ft_dprintf(STDERR_FILENO, SYNTAX_ERR);
		return (1);
	}
	if ((new = start_heredoc_mode(next->value)) == NULL)
		return (1);
	if ((new = env_subst(new)) == NULL)
		return (1);
	free(next->value);
	next->value = new;
	return (0);
}
