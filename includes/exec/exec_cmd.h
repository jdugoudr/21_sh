/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:17:12 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/07 14:39:14 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "token_define.h"
#include "libft.h"///////////////////////////

# define READ_END		0
# define WRITE_END		1
# define CLOSE_OUTPUT	"/dev/null"

int	exec_semi_col(t_ast *el);
int	exec_and_if(t_ast *el);
int	exec_or_if(t_ast *el);
int	exec_and_if(t_ast *el);
int	exec_or_if(t_ast *el);
int	exec_pipe(t_ast *el);
int	exec_less(t_ast *el);
int	exec_dless(t_ast *el);
int	exec_great(t_ast *el);
int	exec_dgreat(t_ast *el);
int	exec_sub_shell(t_ast *el);
int	exec_assign(t_ast *el);
int	exec_word(t_ast *el);

#endif
