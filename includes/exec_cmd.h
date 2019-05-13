/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <jdugoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:17:12 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/13 13:48:26 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "token_define.h"
# include "libft.h"///////////////////////////
# include "shell21.h"

# define READ_END		0
# define WRITE_END		1
# define CLOSE_OUTPUT	"/dev/null"
# define HERE_DOC		"/tmp/heredoc_21"
# define NB_BUILT		5

typedef struct	s_built
{
	char		*name;
	int			(*func)(char **);
}				t_built;

int	exec_semi_col(t_ast *el, t_ast *head);
int	exec_or_if(t_ast *el, t_ast *head);
int	exec_and_if(t_ast *el, t_ast *head);
int	exec_pipe(t_ast *el, t_ast *head);
int	exec_redirect(t_ast *el, t_ast *head);
int	exec_sub_shell(t_ast *el, t_ast *head);
int	exec_assign(t_ast *el, t_ast *head);
int	exec_word(t_ast *el, t_ast *head);
int	exec_dless_fd(t_ast *el, t_ast *head);

int	check_bin(t_ast *el, t_ast *head);

char	**lsttotab(t_arg *lst);

int	exec_less(t_ast *el, t_ast *head);
int	exec_less_fd(t_ast *el, t_ast *head);
int	exec_dless(t_ast *el, t_ast *head);
int	exec_great(t_ast *el, t_ast *head);
int	exec_great_fd(t_ast *el, t_ast *head);
int	exec_dgreat(t_ast *el, t_ast *head);
int	exec_dgreat_fd(t_ast *el, t_ast *head);

#endif
