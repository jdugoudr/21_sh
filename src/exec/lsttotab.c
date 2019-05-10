/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttotab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:46:39 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/10 15:47:05 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "token_define.h"
#include "libft.h"

static int	lenlst(t_arg *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static int	filltab(char **tabs, t_arg *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		tabs[i] = lst->arg;
		i++;
		lst = lst->next;
	}
	tabs[i] = NULL;
	return (0);
}

char		**lsttotab(t_arg *lst)
{
	int		len;
	char	**tabs;

	len = lenlst(lst);
	tabs = malloc((len + 1) * sizeof(char *));
	if (tabs == NULL)
		return (NULL);
	filltab(tabs, lst);
	return (tabs);
}
