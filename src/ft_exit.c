/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:28:04 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/28 13:44:33 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell21.h"
#include "libft.h"

void			ft_exit(char *message, int to_free, int exit_val)
{
	// restore_default_conf();
	if (message != NULL)
		ft_printf("Error: %s\n", message);
	if (g_editor != NULL)
		restore_default_conf();
	(void)to_free;
	// if (to_free)
		// free_select();
	exit(exit_val);
}