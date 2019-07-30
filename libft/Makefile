# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okuchko <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 16:03:56 by okuchko           #+#    #+#              #
#    Updated: 2019/01/16 16:05:31 by okuchko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/

CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

SRC = ft_abs.c ft_atoi.c ft_bzero.c ft_count_char.c ft_isalnum.c ft_isalpha.c\
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c\
	ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c\
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c\
	ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c\
	ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_sqrt.c ft_str_rev.c ft_strcat.c\
	ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c\
	ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c\
	ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c\
	ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c\
	ft_strswapc.c ft_strtrim.c ft_tolower.c ft_toupper.c\
	ft_strdoublefree.c\
	pf_printf.c pf_spec_work.c pf_iputs.c pf_digit.c pf_ox.c pf_c_s_p_end.c\
	pf_float.c pf_floatnum.c pf_unsigned.c\
	get_next_line.c\
	ft_error.c ft_double_malloc.c ft_atoi_fdf.c\


OBJCTS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))


all: $(NAME)

$(NAME): $(OBJCTS)
	@ar rc $(NAME) $(OBJCTS)
	@ranlib $(NAME)

$(OBJCTS): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CC_FLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
