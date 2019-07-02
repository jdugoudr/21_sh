/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:55:25 by mdaoud            #+#    #+#             */
/*   Updated: 2019/07/01 18:58:24 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYPRESS_H
# define KEYPRESS_H
# include <stdlib.h>

# define RET_KEY			0xA
# define ESC_KEY			0x1B
# define CTRL_A_KEY			0x1
# define CTRL_B_KEY			0x2
# define CTRL_C_KEY			0x3
# define CTRL_D_KEY			0x4
# define CTRL_K_KEY			0xB
# define CTRL_L_KEY			0xC
# define CTRL_P_KEY			0x10
# define CTRL_R_KEY			0x12
# define CTRL_U_KEY			0x15
# define CTRL_W_KEY			0x17
# define SPCE_KEY			0x20
# define BCKSPCE_KEY		0x7F
# define UP_KEY				0x415B1B
# define DOWN_KEY			0x425B1B
# define RIGHT_KEY			0x435B1B
# define LEFT_KEY			0x445B1B
# define DEL_KEY			0x7E335B1B
# define HOME_KEY			0x485B1B
# define END_KEY			0x465B1B
# define SHIFT_UP_KEY		0x41323B315B1B
# define SHIFT_DOWN_KEY		0X42323B315B1B
# define SHIFT_RIGHT_KEY	0X43323B315B1B
# define SHIFT_LEFT_KEY		0X44323B315B1B

/*
** Keypresses
*/
int						dispatch_keypress(unsigned long val);
void					keypress_backspace(void);
void					keypress_ctrl_b(size_t s, size_t e);
void					keypress_ctrl_c(void);
void					keypress_ctrl_k(size_t s, size_t e);
void					keypress_ctrl_l(void);
void					keypress_ctrl_p(void);
void					keypress_ctrl_u(void);
void					keypress_delete(void);
void					keypress_downarrow(void);
void					keypress_end(void);
void					keypress_home(void);
void					keypress_shift_down(void);
void					keypress_shift_left(void);
void					keypress_shift_right(void);
void					keypress_shift_up(void);
void					keypress_uparrow(void);

#endif
