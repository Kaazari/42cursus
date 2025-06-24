###############################################
#	SOURCES

SRC		=	pipex.c \

OBJ		= $(SRC:.c=.o)

CC		= cc

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
	$(RM) $(LIBFT)

re:			fclean all

.PHONY:		all clean fclean re
