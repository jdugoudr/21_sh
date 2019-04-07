/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:16:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/06 19:56:52 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static t_ast	*looking_token(t_ast *start, t_ast *end, short level_prior)
{
	t_ast	*el;

	el = start;
	while (el != end && el->level_prior < level_prior)
		el = el->next;
	if (el == end)
		return (NULL);
	return (el);
}

static t_ast	*build_tree(t_ast *start, t_ast *end, short level_prior)
{
	t_ast		*el;

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
	return (0);
}
