###############################################
#	SOURCES

SRC		=	main.c utils.c init.c actions.c monitor.c parsing.c output.c routine.c \

OBJ		= $(SRC:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

TFLAGS	= -g3 -pthread -fsanitize=thread

RM		= rm -f

NAME	= philo

###############################################
#	MAKE

%.o:	%.c
	@$(CC) $(CFLAGS) $(TFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(OBJ) $(TFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
