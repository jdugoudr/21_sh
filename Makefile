# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 13:52:36 by jdugoudr          #+#    #+#              #
#    Updated: 2019/05/10 19:05:31 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
RM				=	rm -rf
NAME			=	21sh
HEAD_DIR		=	includes
LIB_DIR			=	libft/
LIB_FT			=	libft/libft.a
LIB_HEAD		=	libft/includes

HEADERS			=	ast.h \
					check_next.h \
					exec_cmd.h \
					lexer.h \
					libft.h \
					parser.h \
					sh_error.h \
					shell21.h \
					token_define.h

OBJ_DIR			=	objs/

VPATH			=	includes
VPATH			+=	src \
					src/ast \
					src/builtins \
					src/editor \
					src/exec\
					src/keypress \
					src/lexer \
					src/parser \
					src/parser/check_next \
					src/utils \
					src/expansion


SRC				=	main.c

##################################################
##########			AST					##########
##################################################
SRC				+=	create_ast.c create_token.c del_ast.c del_token.c

##################################################
##########			BUILTINS			##########
##################################################
SRC				+=		builtin_cd.c builtin_echo.c builtin_env.c builtin_setenv.c builtin_unsetenv.c builtin_history.c builtin_exit.c

##################################################
##########			EDITOR				##########
##################################################
SRC				+=	add_char.c command_append.c command_erase.c command_reset.c command_set.c \
					detect_input.c prompt_display.c free_shell.c ft_exit.c init_signal_handlers.c \
					init_term.c move_cursor_home.c move_cursor_left.c move_cursor_right.c remove_char.c \
					restore_default_conf.c command_write.c prompt_set.c set_terminfo.c tputs_char.c \
					clear_string.c prompt_reset.c quotes_balanced.c get_editor_dim.c \
					write_in_visual.c ends_with_newline.c continue_until_balanced.c expression_balanced.c

##################################################
##########			EXEC				##########
##################################################
SRC				+=	run_ast.c exec_pipe.c exec_less.c \
					exec_dless.c exec_great.c exec_dgreat.c exec_sub_shell.c exec_assign.c \
					exec_word.c exec_semi_col.c exec_and_if.c exec_or_if.c \
					exec_dless_fd.c exec_less_fd.c exec_great_fd.c exec_dgreat_fd.c \
					exec_bin.c lsttotab.c

##################################################
##########			KEYPRESS			##########
##################################################
SRC				+=	dispatch_keypress.c keypress_backspace.c keypress_ctrl_b.c \
					keypress_ctrl_k.c keypress_ctrl_l.c keypress_ctrl_p.c \
					start_search_mode.c keypress_ctrl_u.c keypress_delete.c \
					keypress_downarrow.c keypress_end.c keypress_home.c  start_visual_mode.c \
					keypress_shift_down.c keypress_shift_left.c keypress_shift_right.c \
					keypress_shift_up.c keypress_uparrow.c

##################################################
##########			LEXER				##########
##################################################
SRC				+=	and_find.c or_find.c word_find.c consume.c quot_find.c \
					semi_find.c less_find.c great_find.c sub_find.c lexer.c

##################################################
##########			PARSER				##########
##################################################
SRC				+=	check_for_and_or.c check_for_assign.c check_for_dgreat.c \
					check_for_dless.c check_for_great.c check_for_less.c check_for_name.c \
					check_for_pipe.c check_for_semi.c check_for_sub.c check_for_word.c check_for_redir_fd.c \
					create_arg.c parser.c sort_redirect.c sort_arg.c parser_tools.c
#check_for_quot.c 
##################################################
##########			EXPANSION			##########
##################################################
SRC				+=	env_subst.c expansion_tok.c

##################################################
##########			UTILS				##########
##################################################
SRC				+=	add_env_var.c change_directory.c check_cmd_format.c display_history.c \
					free_string_array.c get_count.c get_env_value.c get_env_ind.c history_append.c \
					set_last_history_entry.c free_editor.c split_whitespaces.c

OBJS			=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)
$(NAME): libft $(OBJ_DIR) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LIB_FT) -I $(HEAD_DIR) -I $(LIB_HEAD) -ltermcap

libft:
	@make -C $(LIB_DIR)
	@echo "\n\033[34m\033[1mLibft correctly done.\033[0m\n"

$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@echo $<
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEAD_DIR) -I $(LIB_HEAD)

clean:
	@make clean -C $(LIB_DIR)
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
