/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 09:21:53 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/15 15:27:12 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		ft_toline(char **line, char **str, char *next)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	if (next)
		len = ft_strlen(*str) - ft_strlen(next);
	else
		len = ft_strlen(*str);
	if ((tmp = (char*)ft_memalloc((len + 1) * sizeof(char))))
	{
		ft_strncpy(tmp, *str, len);
		*line = tmp;
		while ((*str)[i] != '\n' && (*str)[i])
			i++;
		if (((*str)[i] && !(*str)[i + 1]) || !(*str)[i])
		{
			ft_strdel(str);
			return ;
		}
		tmp = ft_strdup(next + 1);
	}
	free(str);
	*str = tmp;
}

static t_list	*init_lst(const int fd, t_list **head)
{
	t_list	*el;
	t_fd	el_content;

	el = *head;
	if (*head != NULL)
	{
		while (el)
		{
			if (((t_fd*)(el->content))->fd == fd)
				return (el);
			el = el->next;
		}
	}
	el_content.str = NULL;
	el_content.fd = fd;
	if ((el = ft_lstnew(&el_content, sizeof(t_fd))) == NULL)
		return (NULL);
	if (*head == NULL)
	{
		*head = el;
		return (*head);
	}
	ft_lstadd(head, el);
	return (el);
}

static int		rd(t_list **h, t_list **el, char **str, char **line)
{
	int				r;
	char			buff[BUFF_SIZE + 1];
	char			*next;

	while ((next = ft_strchr(*str, '\n')) == NULL)
	{
		if ((r = read(((t_fd*)((*el)->content))->fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[r] = '\0';
		if ((*str = ft_strjoinfree(str, buff)) == NULL)
			return (-1);
		else if (r == 0 && (*str)[0] == '\0')
		{
			ft_lstremove(h, el, &del_fd);
			return (0);
		}
		else if (r == 0)
			break ;
	}
	ft_toline(line, str, next);
	return (1);
}

void			del_fd(void *del)
{
	free(((t_fd*)(del))->str);
	((t_fd*)(del))->str = NULL;
	free(del);
	del = NULL;
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head = NULL;
	t_list			*el;

	if (!line || fd < 0 || BUFF_SIZE < 0 || (el = init_lst(fd, &head)) == NULL)
		return (-1);
	if (((t_fd*)(el->content))->str == NULL)
		((t_fd*)(el->content))->str = (char*)ft_memalloc(sizeof(char));
	return (rd(&head, &el, &(((t_fd*)(el->content))->str), line));
}
