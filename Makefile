# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 13:52:36 by jdugoudr          #+#    #+#              #
#    Updated: 2019/03/30 18:59:28 by mdaoud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	clang
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -rf
NAME			=	21sh
HEAD_DIR		=	includes
LIB_DIR			=	libft/
LIB_FT			=	libft/libft.a
LIB_HEAD		=	$(addprefix $(LIB_DIR), $(HEAD_DIR))

HEADERS			=		libft.h \
						shell21.h

OBJ_DIR			=	objs/
VPATH			=	src \
					src/keypress \
					src/line_editing \
					src/builtins \
					src/utils

VPATH			+=	includes
SRCS			=	builtin_cd.c \
					builtin_echo.c \
					builtin_env.c \
					builtin_setenv.c \
					builtin_unsetenv.c \
					main.c \
					command_erase.c \
					clear_buf.c \
					add_char.c \
					detect_input.c \
					display_prompt.c \
					exec_cmd.c \
					ft_exit.c \
					init_signal_handlers.c \
					init_term.c \
					move_cursor_home.c \
					move_cursor_left.c \
					move_cursor_right.c \
					remove_char.c \
					command_append.c \
					command_reset.c \
					command_set.c \
					restore_default_conf.c \
					rewrite_lines.c \
					tputs_char.c \
					dispatch_keypress.c \
					keypress_backspace.c \
					keypress_ctrl_l.c \
					keypress_ctrl_r.c \
					keypress_ctrl_u.c \
					keypress_delete.c \
					keypress_downarrow.c \
					keypress_end.c \
					keypress_home.c \
					keypress_leftarrow.c \
					keypress_rightarrow.c \
					keypress_shift_down.c \
					keypress_shift_left.c \
					keypress_shift_right.c \
					keypress_shift_up.c \
					keypress_uparrow.c \
					add_env_var.c \
					change_directory.c \
					check_cmd_format.c \
					display_history.c \
					free_string_array.c \
					get_count.c \
					get_env_value.c \
					get_var_ind.c \
					history_append.c \
					set_last_history_entry.c \
					set_prompt.c

OBJS			:=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)
$(NAME): libft $(OBJ_DIR) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LIB_FT) -I $(HEAD_DIR) -I $(LIB_HEAD) -ltermcap
libft:
	@make -C $(LIB_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@echo $<
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEAD_DIR) -I $(LIB_HEAD)
$(OBJ_DIR):
	mkdir $@
clean:
	@make clean -C $(LIB_DIR)
	@$(RM) $(OBJS)
fclean: clean
	@make fclean -C $(LIB_DIR)
	@$(RM) $(NAME)
re: fclean all
.PHONY: all libft clean fclean re