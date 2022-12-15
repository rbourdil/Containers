NAME = containers

OBJS = main.o

HEADS = iterator/iterator_adaptors.hpp iterator/iterator_primitives.hpp

CC = c++

FLAGS = -std=c++98 -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS):	%.o:%.cpp $(HEADS)
			$(CC) $(FLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
