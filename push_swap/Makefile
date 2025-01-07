#############################################################################################################################

SRC	=	src/main.c\
		src/init_stack.c\
		src/op.c\
		src/actions.c\
		src/actions_2.c\
		src/sort_utils.c\
		src/push_a_utils.c\
		src/push_b_utils.c\
		src/apply.c\
		src/case_a.c\
		src/case_b.c\
		src/parsing.c

OBJ		=	$(SRC:.c=.o)

LIBFT	=	./libft/libft.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra
# -Werror

RM		= 	rm -f

NAME	=	push_swap

#############################################################################################################################

%.o:		%.c
			$(CC) $(CFLAGS) -c $< -o $@ -g3

all:		$(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME):	$(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
			$(RM) $(OBJ)
			${RM} *.o
	@make clean -C ./libft

fclean:		clean
			$(RM) $(NAME) $(OBJ)
			$(RM) $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re
