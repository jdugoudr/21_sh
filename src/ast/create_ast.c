/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:16:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/13 20:54:31 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"
//#include "../print_ast.c"

/*
** Create a abstract tree from the token list.
** It's looking from the biggest pritory (level_1) to the lowest (word_level).
** Each token apply recursively what's appear between himself and the previous
** token with a level_priority sup or egual on the right of the tree,
** and next tokens in the list are applied on his left.
*/

static t_ast	*looking_token(t_ast *start, t_ast *end, int level_prior)
{
	t_ast	*el;

	el = start;
	while (el != end && el->level_prior < level_prior)
		el = el->next;
	if (el == end)
		return (NULL);
	return (el);
}

static t_ast	*build_tree(t_ast *start, t_ast *end, int level_prior, t_ast *father)
{
	t_ast		*el;

	if (level_prior == LEVEL_MIN - 1)
		return (NULL);
	el = looking_token(start, end, level_prior);
	if (el)
	{
		el->father = father;
		el->right = build_tree(start, el, level_prior - 1, el);
		el->left = build_tree(el->next, end, level_prior, el);
	}
	else if (level_prior > LEVEL_MIN)
		el = build_tree(start, end, level_prior - 1, father);
	return (el);
}

int			create_ast(t_ast **root, t_ast *list_head)
{
	if (list_head->next == NULL)
		return (0);
	*root = build_tree(list_head->next, NULL, level_1, NULL);
	return (0);
}
