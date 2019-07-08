/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 17:09:29 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/07/07 14:10:40 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"
#include "token_define.h"
#include "ast.h"
#include "sh_error.h"
#include "libft.h"

/*
** convert_var retrun :
** -1 if an error appeared
** 0  if no error and no need to create new ast element
** 1  if no error and is needed to create new ast element
*/

/*
** We take the new string.
** Split on white space and create a new token with the first
** new string.
*/

static int	will_split(char ***tmp, t_ast **new, char *new_str)
{
	*new = NULL;
	if ((*tmp = ft_strsplit_ws(new_str)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		free(new_str);
		return (-1);
	}
	free(new_str);
	if ((*tmp)[0] == NULL)
		return (0);
	else if ((*new = create_tok_el((*tmp)[0], NULL, NULL)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		ft_tabstrdel(tmp, 0);
		return (-1);
	}
	else
		return (1);
}

int			convert_var(char ***tmp, t_ast **new, t_ast *el, int ret)
{
	char	*new_str;

	if ((new_str = env_subst(ft_strdup(el->value), ret)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, INTERN_ERR);
		return (-1);
	}
	if (new_str[0] == '\0' && el->next
		&& el->next->level_prior == LEVEL_REDI && el->next->type != DLESS_TOK)
	{
		ft_dprintf(STDERR_FILENO, AMBI_REDIR, el->value);
		free(new_str);
		return (-1);
	}
	if (el->type == DQUOT_TOK
		|| (el->next && el->next->level_prior == LEVEL_REDI))
	{
		free(el->value);
		el->value = new_str;
		return (0);
	}
	else
		return (will_split(tmp, new, new_str));
}
