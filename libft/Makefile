# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaoud <mdaoud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 12:38:55 by mdaoud            #+#    #+#              #
#    Updated: 2019/07/08 09:54:31 by jdugoudr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
CC				= 	clang
CFlAGS			=	-Wall -Werror -Wextra
HEADERS			=	includes

SRC				=	./src

FT_PRINTF_DIR	=	ft_printf
FT_PRINTF_FILES =	buff_flush.c \
					buff_pad.c \
					buff_put.c \
					dispatch_handlers.c \
					ft_dprintf.c \
					ft_printf.c \
					handler_char.c \
					handler_float.c \
					handler_int.c \
					handler_pointer.c \
					handler_string.c \
					handler_unsigned.c \
					parse_format.c \
					process_plus.c \
					process_precision.c \
					process_sharp.c \
					process_space.c \
					process_zero.c \
					set_flag.c \
					set_length.c

GNL_DIR			=	gnl
GNL_FILES		=	get_next_line.c

IO_DIR		 	= 	io
IO_FILES		=	ft_putchar_fd.c \
					ft_putchar.c \
					ft_putendl.c \
					ft_putnbr_fd.c \
					ft_putnbr.c \
					ft_putnbrln.c \
					ft_putstr_fd.c \
					ft_putstr.c \
					ft_putstrln.c \
					ft_putstrln.c

MEMORY_DIR		=	memory
MEMORY_FILES	=	ft_bzero.c \
					ft_memalloc.c \
					ft_memccpy.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memdel.c \
					ft_memmove.c \
					ft_memset.c

STRING_DIR		=	string
STRING_FILES	=	ft_atoi.c \
					ft_atol.c \
					ft_ftoa.c \
					ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_isspace.c \
					ft_itoa_base.c \
					ft_itoa.c \
					ft_ltoa_base.c \
					ft_ltoa.c \
					ft_strcat.c \
					ft_strchr.c \
					ft_strclr.c \
					ft_strcmp.c \
					ft_strcontains.c \
					ft_strcpy.c \
					ft_strdel.c \
					ft_strdup_free.c \
					ft_strdup.c \
					ft_strequ.c \
					ft_striter.c \
					ft_striteri.c \
					ft_strjoin.c \
					ft_strlcat.c \
					ft_strlen.c \
					ft_strmap.c \
					ft_strmapi.c \
					ft_strncat.c \
					ft_strncmp.c \
					ft_strncpy.c \
					ft_strndup.c \
					ft_strnequ.c \
					ft_strnew.c \
					ft_strnstr.c \
					ft_strrchr.c \
					ft_strreplace.c \
					ft_strrev.c \
					ft_strsplit_ws.c \
					ft_strsplit.c \
					ft_strstr.c \
					ft_strsub.c \
					ft_strtok.c \
					ft_strtrim.c \
					ft_tabstrdel.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_ultoa.c

MATH_DIR		=	math
MATH_FILES		=	ft_abs.c \
					ft_pow.c \
					ft_max.c \
					ft_min.c


OBJ_DIR			=	./objs

OBJ				=	$(FT_PRINTF_FILES:%.c=$(OBJ_DIR)/$(FT_PRINTF_DIR)/%.o) \
					$(GNL_FILES:%.c=$(OBJ_DIR)/$(GNL_DIR)/%.o) \
					$(IO_FILES:%.c=$(OBJ_DIR)/$(IO_DIR)/%.o) \
					$(MEMORY_FILES:%.c=$(OBJ_DIR)/$(MEMORY_DIR)/%.o) \
					$(STRING_FILES:%.c=$(OBJ_DIR)/$(STRING_DIR)/%.o) \
					$(MATH_FILES:%.c=$(OBJ_DIR)/$(MATH_DIR)/%.o)

ALL_DIR			=	$(OBJ_DIR) \
					$(OBJ_DIR)/$(FT_PRINTF_DIR) \
					$(OBJ_DIR)/$(GNL_DIR) \
					$(OBJ_DIR)/$(IO_DIR) \
					$(OBJ_DIR)/$(MEMORY_DIR) \
					$(OBJ_DIR)/$(STRING_DIR) \
					$(OBJ_DIR)/$(MATH_DIR)

all: $(NAME)

$(NAME): $(ALL_DIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\n\033[1;36mLinking $(NAME)\033[0m\n"

$(ALL_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC)/%.c
	@echo "\033[0;36mCompiling\033[0m $<"
	@$(CC) $(CFlAGS) -o $@ -c $< -I$(HEADERS)

clean:
	@echo "\033[0;33mRemoving\033[0m $(OBJ_DIR)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "\033[0;31mRemoving\033[0m $(NAME)"
	@rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re
