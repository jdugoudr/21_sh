/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_ctrl_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:41:21 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 18:23:05 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keypress.h"
#include "editor.h"

void			keypress_ctrl_u(void)
{
	command_erase();
	command_reset();
	command_write();
}