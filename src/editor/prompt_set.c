/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:59:49 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 18:31:34 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "libft.h"

void			prompt_set(char *str)
{
	ft_bzero(g_editor->prompt, PATH_MAX);
	ft_strcpy(g_editor->prompt, str);
	g_editor->offset = ft_strlen(str);
}