/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell21.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:26:41 by mdaoud            #+#    #+#             */
/*   Updated: 2019/04/02 10:28:07 by mdaoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL21_H
# define SHELL21_H

# include <limits.h>
// # include <linux/limits.h>	//delete
# include <term.h>
# include <termios.h>
# include <libft.h>

# define RET_KEY			0xA
# define ESC_KEY			0x1B
# define CTRL_R_KEY			0x12
# define CTRL_U_KEY			0x15
# define CTRL_L_KEY			0xC
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
** Implementation of the command history using a doubly-linked list.
*/
struct					s_history
{
	char				name[ARG_MAX];
	struct s_history	*prev;
	struct s_history	*next;
};

struct					s_editor
{
	char				cmd[ARG_MAX + 1];	//check arg_max
	char				prompt[PATH_MAX];
	size_t				cur_pos;
	size_t				cmd_sze;
	size_t				line;
	size_t				col;
	size_t				max_line;
	size_t				offset;
	size_t				win_width;
	size_t				win_height;
	struct termios		*term;
	struct termios		*oldterm;
};

struct					s_shell
{
	char				**env;
	struct s_history	*hist;
	struct s_history	*hist_ptr;
};

typedef struct termios		t_termios;
typedef struct s_shell		t_shell;
typedef struct s_editor		t_editor;
typedef struct s_history	t_history;

/*
** We use a global variable for propre handling of signals.
*/
t_editor					*g_editor;

void			ft_exit(char *message, int to_free, int exit_val);
void			restore_default_conf(void);
void			display_prompt(void);
void			free_shell(void);
void			exec_cmd(void);
void			init_term(void);
void			init_signal_handlers(void);

void			detect_input(t_shell *shell);
void			rewrite_lines(void);
void			add_char(char c);
void			remove_char(void);

void			move_cursor_right(void);
void			move_cursor_left(void);
void			move_cursor_home(void);

/*
** Keypresses
*/
int				dispatch_keypress(t_shell *shell, unsigned long key_val);
void			keypress_backspace(void);
void			keypress_ctrl_l(void);
void			keypress_ctrl_r(t_shell *shell);
void			keypress_ctrl_u(void);
void			keypress_delete(void);
void			keypress_downarrow(t_shell *shell);
void			keypress_end(void);
void			keypress_home(void);
void			keypress_leftarrow(void);
void			keypress_rightarrow(void);
void			keypress_shift_down(void);
void			keypress_shift_left();
void			keypress_shift_right(void);
void			keypress_shift_up(void);
void			keypress_uparrow(t_shell *shell);

/*
** Utils
*/
void			add_env_var(char *key, char *val);
void			change_directory(char *path, int print_dir);
int				check_cmd_format(char **cmd, size_t param_num);
void			free_string_array(char **array);
size_t			get_count(char **t);
char			*get_env_value(char *key);
int				get_env_ind(char *env_var);
void			history_append(t_shell *shell, char *name);
void			display_history(t_shell *shell);
void			set_last_history_entry(t_shell *shell);
void			command_append(char *str, int rewrite_flag);
void			command_reset();
void			command_set(char *str, int rewrite_flag);
int				tputs_char(int c);
void			set_prompt(char *str);
void			command_erase(void);
void			clear_buf(char *str, size_t len);

/*
** Builtins
*/
void				builtin_cd(char **cmd);
void				builtin_echo(char **cmd);
void				builtin_env(void);
void				builtin_setenv(char **cmd);
void				builtin_unsetenv(char **cmd);

#endif