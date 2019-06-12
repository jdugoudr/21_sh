/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwa <marwa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:39:22 by mdaoud            #+#    #+#             */
/*   Updated: 2019/01/01 04:04:45 by marwa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*get_token(char **str)
{
	char	*ptr;
	char	*token;
	char	*temp;

	token = *str;
	ptr = ft_strchr(*str, '\n');
	if (ptr == NULL)
		return (NULL);
	*ptr = '\0';
	token = ft_strsub(*str, 0, ptr - token + 1);
	if (token == NULL)
	{
		ft_strdel(&token);
		return (NULL);
	}
	ptr++;
	temp = ft_strdup(ptr);
	ft_strdel(str);
	*str = temp;
	return (token);
}

int			return_line(int read_retval, char *token, char **str, char **line)
{
	if (read_retval < 0)
	{
		ft_strdel(str);
		return (-1);
	}
	if (read_retval == 0 && **str == '\0')
	{
		ft_strdel(str);
		return (0);
	}
	if (read_retval == 0 && token == NULL)
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
		*str = ft_strdup("");
		if (*line == NULL || *str == NULL)
			return (-1);
	}
	else
	{
		*line = ft_strdup(token);
		if (*line == NULL)
			return (-1);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char		*str = NULL;
	char			*token;
	char			buff[GNL_BUFF_SIZE + 1];
	int				read_retval;
	int				retval;

	read_retval = 1;
	if (str == NULL)
		str = ft_strdup("");
	if (fd < 0 || line == NULL)
		return (-1);
	while ((token = get_token(&str)) == NULL)
	{
		if ((read_retval = read(fd, buff, GNL_BUFF_SIZE)) <= 0)
			break ;
		buff[read_retval] = '\0';
		str = ft_strjoin(str, buff, 1);
		ft_bzero(buff, GNL_BUFF_SIZE + 1);
	}
	retval = return_line(read_retval, token, &str, line);
	if (token != NULL)
		ft_strdel(&token);
	return (retval);
}
