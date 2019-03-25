/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 17:24:16 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/03/25 18:24:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEL_AST_H
# define DEL_AST_H

# include "token_define.h"

void	del_token(t_ast **el);
void	del_ast(t_ast **ast_head);

#endif
