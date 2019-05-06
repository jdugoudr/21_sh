/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_dless.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 09:37:52 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/06 19:05:40 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_next.h"
#include "sh_error.h"
#include "ast.h"

#define BUFF	150

static int	add_line(char **line, char *buff, int len_buff, char *tmp)
{
	char	*new;
	int		len_line;
	int		ret;

	ret = 0;
	len_line = ft_strlen(*line);
	if ((new = malloc((len_line + len_buff + 1) * sizeof(char))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		ret = 1;
	}
	else
	{
		new = ft_strcpy(new, *line);
		new[len_line] = '\n';
		new[len_line + 1] = '\0';
		new = ft_strcat(new, buff);
	}
	*line = new;
	(void)tmp;
//	free(tmp);
	return (ret);
}

static int	heredoc_read(char **line, char *end_here)
{
	char	buff[BUFF + 1];
	char	*tmp;
	int		rd;

//	buff[0] = '\0';
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
			if (add_line(line, buff, rd, tmp))
				return (1);
			ft_printf("check_for_dless => %s\n", *line);//////////////
		}
	}
	return (0);
}

int	check_for_dless(t_ast *next, char **line)
{
	char	*new;
	char	*tmp;

	(void)line;
	if ((next->type & AFTER_DLESS) == 0)
		return (1);
	if ((new = ft_strnew(BUFF + 1)) == NULL)
		return (1);
	if (heredoc_read(&new, next->value))
		return (1);
	if ((tmp = env_subst(new, '$')) == NULL)
		return (1);
//	free(next->value);
//	free(new);
	next->value = tmp;
	return (0);
}
