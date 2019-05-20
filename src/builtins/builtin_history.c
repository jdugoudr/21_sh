/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:29:18 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/20 19:40:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"
#include "libft.h"

int			builtin_history(char **cmd)
{
	t_history	*hist;
	char		c;
	int			i;

	(void)cmd;
	hist = g_shell->hist;
	i = 0;
	while (hist != NULL)
	{
		i++;
		c = i + '0';
		write(STDOUT_FILENO, &c, 1);
		write(STDOUT_FILENO, " - ", 3);
		write(STDOUT_FILENO, hist->name, ft_strlen(hist->name));
		write(STDOUT_FILENO, "\n", 1);
		hist = hist->next;
	}
	return (0);
}
