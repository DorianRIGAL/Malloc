##
## EPITECH PROJECT, 2018
## PSU_2018_malloc
## File description:
## Makefile
##

SRC	=	malloc.c	\
		side_malloc.c	\
		show_alloc_mem.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror -W -I./include -fpic

NAME	=	libmy_malloc.so

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -shared -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean all
