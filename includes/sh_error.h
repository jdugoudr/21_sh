/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 16:25:45 by jdugoudr          #+#    #+#             */
/*   Updated: 2019/05/09 15:09:55 by jdugoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ERROR_H
# define SH_ERROR_H

# define INTERN_ERR	"21sh: Sorry an intern issue appeared. Please try again.\n"

/*
** Parse error
*/
# define SYNTAX_ERR	"21sh: Syntax error\n"

/*
** Lexer error
*/
# define UNEX_SYMB	"21sh: Error unexpected symbol %c\n"

/*
** Exec error
*/
# define BAD_FD		"21sh: %s: Bad file desciptor\n"
# define AMBI_REDIR	"21sh: %s: Ambiguous redirect\n"
# define CANT_OPEN	"21sh: %s: Failed to open\n"
# define NO_CMD		"21sh: %s: Command not found\n"

#endif
