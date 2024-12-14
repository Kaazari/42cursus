#############################################################################################################################

SRC	=	src/so_long.c\
		src/hookers.c\
		src/map_reader.c\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		src/error.c\

OBJ		=	$(SRC:.c=.o)

MLX		=	mlx_linux/

CC		=	cc

MLX_FLAG=	-I mlx_linux -Lmlx_linux -lmlx -lXext -lX11 -lm

CFLAGS	=	-Wall -Wextra -Werror

RM		= 	rm -f

NAME	=	so_long

#############################################################################################################################

%.o:		%.c
			$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@ -g3

all:		$(NAME)

mlx:
	@make -sC $(MLX)

$(NAME):	 mlx $(OBJ)
			$(CC) $(OBJ)  $(MLX)/libmlx.a $(MLX_FLAG) -o $(NAME)
clean:
			$(RM) $(OBJ)
	@make clean -C $(MLX)

fclean:		clean
			$(RM) $(NAME) $(OBJ)

re:			fclean all

.PHONY:		all clean fclean re
