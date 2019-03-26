# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 13:52:36 by jdugoudr          #+#    #+#              #
#    Updated: 2019/03/26 10:11:13 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
NAME = 21sh
HEAD_DIR = -I includes -I includes/parser -I includes/lexer -I includes/error \
		   -I includes/ast
LIB_DIR = libft/
LIB_FT = libft/libft.a
LIB_HEAD = libft/includes
OBJ_DIR = objs/
VPATH = srcs \
		srcs/parser \
		srcs/parser/check_next \
		srcs/lexer \
		srcs/ast
VPATH += includes \
		 includes/lexer \
		 includes/parser \
		 includes/error \
		 includes/ast
##########################################
SRCS = main.c
######################
#	files for lexer
######################
SRCS += lexer.c
#	token detector
SRCS += and_find.c or_find.c word_find.c consume.c quot_find.c semi_find.c \
		less_find.c great_find.c sub_find.c
######################
#	files for parser
######################
SRCS += parser.c
#	check syntax
SRCS += check_for_and_or.c check_for_pipe.c check_for_word.c \
	   check_for_name.c check_for_assign.c check_for_quot.c check_for_semi.c \
	   check_for_dless.c check_for_less.c check_for_great.c \
	   check_for_dgreat.c check_for_sub.c
#	AST
SRCS += del_ast.c del_token.c
##########################################
HEADERS = 21sh.h \
		  lexer.h \
		  token_define.h \
		  parser.h \
		  sh_error.h \
		  check_next.h \
		  del_ast.h
##########################################
OBJS:= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)
	@:

$(NAME): libft $(OBJ_DIR) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LIB_FT) $(HEAD_DIR) -I $(LIB_HEAD)
	@echo "\n\033[34m\033[1m$(NAME) correctly done.\033[0m\n"

libft:
	@make -C $(LIB_DIR) 
	@echo "\n\033[34m\033[1mLibft correctly done.\033[0m\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@echo $<
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEAD_DIR) -I $(LIB_HEAD)

$(OBJ_DIR):
	@mkdir $@

clean:
	@make clean -C $(LIB_DIR)
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re 
