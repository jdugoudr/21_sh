/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 19:03:02 by mdaoud            #+#    #+#             */
/*   Updated: 2019/06/10 19:03:03 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

size_t			get_env_var_count(char **t)
{
	size_t		count;

	count = 0;
	while (t[count] != NULL)
		count++;
	return (count);
}
