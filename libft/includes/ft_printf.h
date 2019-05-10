/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:28:42 by mdaoud            #+#    #+#             */
/*   Updated: 2019/05/10 17:05:07 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

# define SHARP_F 1
# define ZERO_F 2
# define MINUS_F 4
# define SPACE_F 8
# define PLUS_F 16
# define DOT_F	32
# define PF_BUFF_SIZE 10

typedef struct	s_pf_arg
{
	char	type;
	char	buff[PF_BUFF_SIZE + 1];
	int		fd;
	int		flags;
	int		width;
	int		precision;
	int		length;
	int		stars;
	int		it;
}				t_pf_arg;

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				parse_format(int fd, char *c, va_list ap, int *percent);
int				dispatch_handlers(t_pf_arg *arg, char type, va_list ap);
int				buff_put(t_pf_arg *arg, char *c, size_t len);
void			buff_write(t_pf_arg *arg);
void			buff_flush(t_pf_arg *arg);
int				buff_pad(t_pf_arg *arg, char c, int len);

/*
** Handlers
*/
int				handler_int(t_pf_arg *arg, va_list ap);
int				handler_char(t_pf_arg *args, va_list ap);
int				handler_unsigned(t_pf_arg *arg, va_list ap);
int				handler_string(t_pf_arg *arg, va_list ap);
int				handler_float(t_pf_arg *arg, va_list ap);
int				handler_pointer(t_pf_arg *arg, va_list ap);

/*
** Flag Processing
*/
int				process_precision(t_pf_arg *arg, char *str, int len);
int				process_width(t_pf_arg *arg);
int				process_zero(t_pf_arg *arg, char *str);
char			*process_space(t_pf_arg *arg, char *str);
char			*process_plus(t_pf_arg *arg, char *str);
char			*process_sharp(t_pf_arg *arg, char *str);

/*
** Utility
*/
void			set_flag(t_pf_arg *arg, char *c, va_list ap);
void			set_length(t_pf_arg *arg, char c);

#endif
