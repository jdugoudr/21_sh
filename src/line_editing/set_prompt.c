/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:59:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/03/30 18:36:16 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void			set_prompt(char *str)
{
	ft_bzero(g_editor->prompt, PATH_MAX);
	ft_strcpy(g_editor->prompt, str);
	g_editor->offset = ft_strlen(str);
}