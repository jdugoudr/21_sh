/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:16:08 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/06/15 14:55:01 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

/*
** Create a abstract tree from the token list.
** It's looking from the biggest pritory (level_1) to the lowest (word_level).
** Each token apply recursively what's appear between himself and the previous
** token with a lvl_ptyity sup or egual on the right of the tree,
** and next tokens in the list are applied on his left.
** The leaf of the tree are the command line.
** The commande could constitute of redirection, assignation and/or command
** The parents of a leaf point to the token the most on the right :
** ls > f && < f cat
** The token '&&' will point on the left to 'f' and on the right to 'cat'
*/

static t_ast	*looking_token(t_ast *start, t_ast *end, int lvl_pty)
{
	t_ast	*el;

	el = start;
	while (el != end && el->level_prior < lvl_pty)
		el = el->next;
	if (el == end)
		return (NULL);
	return (el);
}

static t_ast	*build_tree(t_ast *start, t_ast *end, int lvl_pty, t_ast *fth)
{
	t_ast		*el;

	if (start != end && lvl_pty == LEVEL_REDI)
	{
		start->father = fth;
		return (start);
	}
	el = looking_token(start, end, lvl_pty);
	if (el && lvl_pty > LEVEL_REDI)
	{
		el->father = fth;
		el->right = build_tree(start, el, lvl_pty - 1, el);
		el->left = build_tree(el->next, end, lvl_pty, el);
	}
	else if (lvl_pty > LEVEL_REDI)
		el = build_tree(start, end, lvl_pty - 1, fth);
	return (el);
}

int				create_ast(t_ast **root, t_ast *list_head)
{
	if (list_head->next == NULL)
		return (0);
	*root = build_tree(list_head->next, NULL, level_1, NULL);
	return (0);
}
