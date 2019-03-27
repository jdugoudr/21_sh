/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:16:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/27 13:50:43 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

///////// delete this function before merge master !!

void	print_token(t_ast *tok)
{
	t_ast *el;

	el = tok;
	while (el)
	{
		ft_printf("actuel token => %s\n", el->value);
		ft_printf("actuel type => %d\n", el->type);
		el = el->next;
	}
}
////// for debug
void	print_one(t_ast *el, int ind)
{
	if (!el)
	{
		ft_printf("print el : NULL\n");
		return ;
	}
	ft_printf("%*c type : %d\n", ind, ' ', el->type);
	ft_printf("%*c level : %d\n", ind, ' ', el->level_prior);
	ft_printf("%*c value : %s\n", ind, ' ', el->value);
}
////// for debug
void	print_ast(t_ast *el, int ind)
{
	if (el->left)
	{
		print_ast(el->left, ind + 10);
	}
	if (el->right)
	{
		print_one(el, ind);
		print_ast(el->right, ind + 10);
	}
	else
		print_one(el, ind);
}

static t_ast	*looking_token(t_ast *start, t_ast *end, short level_prior)
{
	t_ast	*el;

	el = start;
	while (el != end && el->level_prior < level_prior)
	{

		el = el->next;
	}
	if (el == end)
		return (NULL);
	return (el);
}

static t_ast	*build_tree(t_ast *start, t_ast *end, short level_prior)
{
	t_ast	*el;

	if (level_prior == LEVEL_MIN - 1)
		return (NULL);
	el = looking_token(start, end, level_prior);
	if (el)
	{
		el->right = build_tree(start, el, level_prior - 1); //tu regardes ce qui  l'y a D
		el->left = build_tree(el->next, end, level_prior); //tu regardes ce qui l'y a G
	}
	else if (level_prior > LEVEL_MIN)
		el = build_tree(start, end, level_prior - 1);
	return (el);
}

int			create_ast(t_ast **root, t_ast *list_head)
{
	if (list_head->next == NULL)
		return (0);
	*root = build_tree(list_head->next, NULL, level_1);
	print_ast(*root, 0);//////// just for debug
	return (0);
}
