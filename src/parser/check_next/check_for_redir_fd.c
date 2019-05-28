/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_redir_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:44:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/28 10:35:53 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"
#include "sh_error.h"
#include "libft.h"

static int	close_redirect(char **value, char **line, int pos)
{
	int		back;
	char	*tmp;

	back = 1;
	while ((*value)[pos + back] && (*value)[pos + back] != ' ')
		back++;
	if (back > 1)
	{
		if ((tmp = ft_strndup((*value), pos + 1)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, INTERN_ERR);
			return (-1);
		}
		free(*value);
		*value = tmp;
		(*line) -= (back - 1);
	}
	return (0);
}

static int	is_valid(char **value, char **line)
{
	int	size;

	size = 0;
	if ((*value)[size] == '-')
		return (close_redirect(value, line, size));
	else
	{
		while (ft_isdigit((*value)[size]))
			size++;
		if ((*value)[size] == '-' && (*value)[size + 1] == '-')
		{
			ft_dprintf(STDERR_FILENO, AMBI_REDIR, (*value) + 1);
			return (-1);
		}
		else if ((*value)[size] == '-')
			return (close_redirect(value, line, size));
	}
	return (0);
}

int			check_for_redir_fd(t_ast *next, char **line)
{
	if ((next->type & AFTER_REDIR_FD) == 0)
		return (1);
	return (is_valid(&(next->value), line));
}
