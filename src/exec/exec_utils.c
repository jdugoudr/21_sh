/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:19:34 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/14 14:14:24 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "sh_error.h"
#include "libft.h"

void	del_saved_fd(int ***tab_)
{
	int i;

	i = 0;
	while (*tab_ && (*tab_)[i])
	{
		free((*tab_)[i]);
		i++;
	}
	free(*tab_);
	*tab_ = NULL;
}

int	is_saved(int **tab_, int fd, int type)
{
	int	i;

	i = 0;
	if (!tab_)
		return (0);
	while (tab_[i])
	{
		if (tab_[i][type] == fd)
			return (1);
		i++;
	}
	return (0);
}

int	**add_value(int **tab_, int to_save, int saved)
{
	int	i;
	int	**new_tab;
	int	*new_el;

	i = 0;
	while (tab_ && tab_[i])
		i++;
	new_tab = malloc((i + 2) * sizeof(int *));
	new_el = malloc(2 * sizeof(int));
	if (!new_el || !new_tab)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		free(new_tab);
		free(new_el);
		del_saved_fd(&tab_);
	}
	new_el[0] = to_save;
	new_el[1] = saved;
	new_tab[i] = new_el;
	new_tab[i + 1] = NULL;
	i = 0;
	while (tab_ && tab_[i])
	{
		new_tab[i] = tab_[i];
		i++;
	}
	free(tab_);
	return (new_tab);
}