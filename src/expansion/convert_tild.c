/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_tild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 16:31:31 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/16 16:32:05 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_define.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"

int	convert_tild(char **str)
{
	char	*tmp;
	char	*value;

	if ((value = get_env_value("HOME")) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	tmp = *str;
	*str = ft_strjoin(value, *str + 1, 1);
	free(tmp);
	if (*str == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (1);
	}
	return (0);
}
