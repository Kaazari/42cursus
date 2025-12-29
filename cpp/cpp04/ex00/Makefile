#####################################################################
##########################

NAME		= animal

CXX			= c++

CXX_FLAGS	= -Wall -Wextra -Werror -std=c++98

#####################

SRCS		= main.cpp Animal.cpp WrongAnimal.cpp Cat.cpp WrongCat.cpp Dog.cpp \

OBJS		= $(SRCS:.cpp=.o)

###################

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	@make clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
