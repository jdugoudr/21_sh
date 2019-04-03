/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 22:17:03 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/03 20:21:35 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdio.h"////////////////////////////////
#include "token_define.h"
#include "parser.h"
#include "libft.h"

////test
void print_list(t_ast *start)
{
	t_ast	*el;

	el = start;
	while (el)
	{
		ft_printf("value list %s\n", el->value);
		el = el->next;
	}
}

static void		swap_el(t_ast *a, t_ast *b, t_ast *prev)
{
	t_ast	*tmp;

	prev->next = prev->next->next->next;
	prev->next->prev = prev;
	tmp = a->next->next;
	a->next->next = b;
	b->next->next = tmp;
	b->prev = a->next;
//	print_list(prev);
//	ft_printf("\n\n");
}

static t_ast	*swap_redir(t_ast *start, t_ast *end, short type_redir, int nb)
{
	t_ast		*el;
	t_ast		*save;
	int			count;

	el = start;
	count = nb + 1;
	if (nb == 0)
		return (start);
	while ((el->next->type & type_redir) == 0)
		el = el->next;
	save = el;
	while (count > 0)
	{
		if ((el->next->type & type_redir)/* == 0*/)
		{
			count--;
		}
		if (count > 0)
			el = el->next;
	}
	swap_el(el, save, save->prev);
	return (swap_redir(start, end, type_redir, nb - 1));
}

static int	count_redir(t_ast *start, t_ast *end, short type_redir)
{
	t_ast	*el;
	int		count;

	count = 0;
	el = start;
	while (el != end)
	{
		if (el->type & type_redir)
			count++;
		el = el->next;
	}
	return (count);
}

t_ast	*sort_redirect(t_ast *start, t_ast *end)
{
	int	nb_red;

	nb_red = count_redir(start, end, LESS_TOK | DLESS_TOK);
	if (nb_red > 1)
		start = swap_redir(start, end, LESS_TOK | DLESS_TOK, nb_red - 1);
//	ft_printf("start %s\n", start->value);
//	ft_printf("en definitive\n");////////////////
//	print_list(start);/////////
	return (start);
}
