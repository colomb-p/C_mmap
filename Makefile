NAME		=	mmap
CC		=	gcc
CFLAGS		=
SRC		=	main.c
OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		@echo "Deleting binary $(NAME)"
		@rm -f $(NAME)

fclean:		clean
		@echo "Deleting obj files $(OBJ)"
		@rm -f $(OBJ)

re:		fclean	all

.phony:		all	clean	fclean	re
