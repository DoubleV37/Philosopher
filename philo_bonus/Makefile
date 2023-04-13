# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviovi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 11:12:09 by vviovi            #+#    #+#              #
#    Updated: 2023/04/05 15:54:24 by vviovi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = philo_bonus

SRC =	srcs/main_bonus.c \
		srcs/utils_bonus.c \
		srcs/routine_bonus.c \
		srcs/parsing_bonus.c

RM = rm -rf

MAKEFLAGS =	--no-print-directory

OBJ =	$(SRC:srcs/%.c=objs/%.o)

OBJ_DIR = objs

CFLAGS = -Wall -Wextra -Werror -g3 -pthread

all:	$(NAME)

objs/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $^ -o $(<:srcs/%.c=objs/%.o)

$(OBJ_DIR):
		mkdir $@

$(NAME):	$(OBJ_DIR) $(OBJ)
		@echo "**********************"
		@echo "*     \033[1;33mCOMPILING\033[1;0m      *"
		@echo "**********************\n"
		$(CC) $(CFLAGS) $(OBJ) -o $@
		@echo "**********************"
		@echo "*        \033[1;32mDONE\033[1;0m        *"
		@echo "**********************"

clean:
		$(RM) $(OBJ_DIR)
		@echo "**********************"
		@echo "*    \033[1;32mCLEANED OBJS\033[1;0m    *"
		@echo "**********************"

fclean:
		$(RM) $(OBJ_DIR) $(NAME)
		@echo "**********************"
		@echo "*     \033[1;32mCLEANED ALL\033[1;0m    *"
		@echo "**********************"

re:		fclean	all

bonus : all

.PHONY:	all clean fclean re bonus
