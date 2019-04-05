/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:00:21 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/04/05 14:50:16 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_AST_H
# define RUN_AST_H

# include "token_define.h"

# define RUN_AFTER	(AND_IF | OR_IF)
# define NOT_DO_R	(LESS_TOK | DLESS_TOK | GREAT_TOK | DGREAT_TOK)

int	run_ast(t_ast *root);

#endif
