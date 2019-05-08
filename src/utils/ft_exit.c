/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 17:28:04 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/24 18:27:50 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell21.h"
#include "libft.h"

void	ft_exit(char *message, int restore_flag, int free_flag, int exit_val)
{
	if (message != NULL)
		dprintf(STDERR_FILENO, "Error: %s\n", message);
	if (restore_flag)
		restore_default_conf();
	if (free_flag)
		free_editor();
	exit(exit_val);
}