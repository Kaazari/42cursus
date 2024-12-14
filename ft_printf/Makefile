# #Variables

# NAME		= libftprintf.a
# INCLUDE		= include
# LIBFT		= libft
# SRC_DIR		= srcs/
# OBJ_DIR		= obj/
# CC			= gcc
# CFLAGS		= -Wall -Werror -Wextra -I
# RM			= rm -f
# AR			= ar rcs

# # Colors

# DEF_COLOR = \033[0;39m
# GRAY = \033[0;90m
# RED = \033[0;91m
# GREEN = \033[0;92m
# YELLOW = \033[0;93m
# BLUE = \033[0;94m
# MAGENTA = \033[0;95m
# CYAN = \033[0;96m
# WHITE = \033[0;97m

# #Sources

# SRC_FILES	=	ft_printf.c \
# 					ft_ptr.c \
# 					ft_whatif.c


# SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

# ###


# all:		$(NAME)

# $(NAME):
# 			@make -C $(LIBFT)
# 			@cp libft/libft.a .
# 			@mv libft.a $(NAME)
# 			@$(AR) $(NAME)
# 			@echo "$(GREEN)ft_printf compiled!$(DEF_COLOR)"

# $(SRC_DIR)%.c:
# 			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
# 			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# clean:
# 			@$(RM) -f *.o
# 			@make clean -C $(LIBFT)
# 			@echo "$(BLUE)ft_printf object files cleaned!$(DEF_COLOR)"

# fclean:		clean
# 			@$(RM) -f $(NAME)
# 			@$(RM) -f $(LIBFT)/libft.a
# 			@echo "$(CYAN)ft_printf executable files cleaned!$(DEF_COLOR)"
# 			@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

# re:			fclean all
# 			@echo "$(GREEN)Cleaned and rebuilt everything for ft_printf!$(DEF_COLOR)"

# norm:
# 			@norminette $(SRC) $(INCLUDE) $(LIBFT) | grep -v Norme -B1 || true

# .PHONY:		all clean fclean re norm

#########################################################
#	#	#	#	#

SRCS			=	srcs/ft_printf.c \
					srcs/ft_ptr.c \
					srcs/ft_whatif.c

OBJS			= 	${SRCS:.c=.o}

LIBFT			=	libft

#########################################################
#	#	#	#	#

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -I.
RM				=	rm -f

NAME			=	libftprintf.a

#########################################################
#	#	#	#	#

all:			${NAME}

$(NAME):		$(OBJS)
				make -C $(LIBFT)
				cp libft/libft.a .
				mv libft.a $(NAME)
				ar rcs $(NAME) $(OBJS)

%.o:			%.c
				${CC} ${CFLAGS} -c $< -o $@

clean:
				${RM} *.o

fclean:			clean
				${RM} ${NAME} ${OBJS}

re:				fclean all

.PHONY:			all clean fclean re
