/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_dless.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:37:52 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/07 11:10:57 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"
#include "sh_error.h"
#include "ast.h"

#define BUFF	150

/*
** We read on std_in until next->value are found.
** The new line is stock in next->value
*/

static int	add_line(char **line, char *buff, int len_buff)
{
	char	*new;
	int		len_line;
	int		ret;

	ret = 0;
	len_line = ft_strlen(*line);
	if ((new = malloc((len_line + len_buff + 2) * sizeof(char))) == NULL)
	{
		free(*line);
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		ret = 1;
	}
	else
	{
		new[0] = '\0';
		if (len_line)
		{
			new = ft_strcpy(new, *line);
			new[len_line] = '\n';
			new[len_line + 1] = '\0';
		}
		new[len_line + len_buff + 1] = '\0';
		new = ft_strcat(new, buff);
		free(*line);
	}
	*line = new;
	return (ret);
}

static int	heredoc_read(char **line, char *end_here)
{
	char	buff[BUFF + 1];
	char	*tmp;
	int		rd;

	while (1)
	{
		ft_dprintf(STDIN_FILENO, "> ");
		if ((rd = read(STDIN_FILENO, buff, BUFF)) == -1)
		{
			free(*line);
			return (1);
		}
		tmp = *line;
		buff[rd - 1] = '\0';
		if (ft_strcmp(buff, end_here) == 0)
			break ;
		else 
		{
			if (add_line(line, buff, rd))
				return (1);
		}
	}
	return (0);
}

int	check_for_dless(t_ast *next, char **line)
{
	char	*new;

	(void)line;
	if ((next->type & AFTER_DLESS) == 0)
		return (1);
	if ((new = ft_strnew(BUFF + 1)) == NULL)
		return (1);
	if (heredoc_read(&new, next->value))
		return (1);
	if ((new = env_subst(new)) == NULL)
		return (1);
	free(next->value);
	next->value = new;
	return (0);
}
