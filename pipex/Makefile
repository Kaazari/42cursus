###############################################
#	SOURCES

SRC		=	bonus.c \

OBJ		= $(SRC:.c=.o)

CC		= cc
# CC		= gcc

CFLAGS	= -Wall -Wextra
# -Werror

LIBFT	= ./libft/libft.a

RM		= rm -f

NAME	= pipex

###############################################
#	MAKE

%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -g3

all:	$(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME):	$(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJ)
	@make clean -C ./libft

fclean:		clean
	$(RM) $(NAME)
	@make fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re
