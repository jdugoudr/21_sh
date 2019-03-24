# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdugoudr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/22 13:52:36 by jdugoudr          #+#    #+#              #
#    Updated: 2019/03/24 14:09:33 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
NAME = 21sh
HEAD_DIR = -I includes
LIB_DIR = libft/
LIB_FT = libft/libft.a
LIB_HEAD = libft/includes
OBJ_DIR = objs/
VPATH = srcs
VPATH += includes
SRCS = 21sh.c
HEADERS = 21sh.h
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
