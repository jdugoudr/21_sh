/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:05:30 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/24 13:15:37 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "flags.h"

int	manage_f(t_convert *t, t_flags *flags, va_list *ap)
{
	t_fcfl		tabf[NB_FLAGS];

	init_tabf(tabf);
	if ((flags->fc & PR_FLAG) == 0)
	{
		flags->fc |= PR_FLAG;
		flags->precision = ft_strdup("6");
	}
	if (flags->fc & LLL_FLAG)
	{
		if ((t->value = ft_ldbtoa(va_arg(*ap, long double))) == NULL)
			printf_error(ERR_STR, NULL);
	}
	else
	{
		if ((t->value = ft_dbtoa(va_arg(*ap, double))) == NULL)
			printf_error(ERR_STR, NULL);
	}
	return (run_flags(t, flags, tabf));
}
