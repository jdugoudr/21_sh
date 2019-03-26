/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:46:25 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 15:21:14 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include "lexer.h"
#include "parser.h"

#define BUFF	50

static int	mn_gnl(char **line)
{
	char	buff[BUFF + 1];
	char	*tmp;
	int		rd;
	int		nb;

	nb = 1;
	if ((*line = ft_strnew(BUFF + 1)) == NULL)
		return (1);
	while ((tmp = ft_strchr(*line, '\n')) == NULL)
	{
		if ((rd = read(STDIN_FILENO, buff, BUFF)) == -1)
		{
			free(*line);
			return (1);
		}
		buff[rd] = '\0';
		if ((*line = ft_strjoinfree(line, buff)) == NULL)
			return (1);
	}
	*(*line + (tmp - *line)) = '\0';
	return (0);
}

int			main(void)
{
	char	*line;

	if (mn_gnl(&line) == 0)
	{
		parser(line);
		free(line);
	}
	return (1);
}
