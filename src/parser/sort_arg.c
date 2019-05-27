
#include "token_define.h"
#include "libft.h"
#include "parser.h"

/*
** Check all word tokens betwen two tokens with level priority up to level
** redirect.
** And place all of them one after one.
** ls > file -l   ==> ls -l > file
*/

static int	count_arg(t_ast *el, t_ast *end)
{
	int	count;

	count = 0;
	while (el != end && el->type == WORD_TOK)
	{
		el = el->prev;
		count++;
	}
	return (count);
}

static int		skip(t_ast *el, t_ast *end)
{
	int	count;

	count = 0;
	while (el != end && el->level_prior == level_4)
	{
		el = el->prev->prev;
		count += 2;
	}
	return (count);
}

static int		go_to_first(t_ast **el, t_ast *end)
{
	int	i;
	int	count_skip;

	i = 0;
	if (*el == NULL || (*el)->prev == NULL)
		return (0);
	count_skip = skip((*el)->prev, end);
	while (i++ <= count_skip)
		*el = (*el)->prev;
	return (i);
}

static t_ast	*loop_sort(t_ast *start, t_ast *end)
{
	t_ast	*el;
	t_ast	*tmp;
	t_ast	*tmp_2;
	int		count_move;
	int		i;

	el = start;
	i = go_to_first(&el, end);
	count_move = count_arg(el, end);
	if (count_move == 0)
		return (end);
	tmp = start->prev;
	start->prev = el;
	el->next = start;
	while (count_move-- > 1)
		el = el->prev;
	tmp_2 = el->prev;
	el->prev = tmp;
	tmp->next = el;
	while (--i > 2)
		tmp = tmp->prev;
	tmp->prev = tmp_2;
	tmp_2->next = tmp;
	return (loop_sort(el, end));
}

t_ast	*sort_arg(t_ast *start, t_ast *end)
{
	t_ast	*el;

	el = start;
	while (el != end && el->prev != end && el->prev->type == WORD_TOK)
		el = el->prev;
	return (loop_sort(el, end));
}
