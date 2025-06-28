CPP = c++
COMPILE_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g -c
LINK_FLAGS = 
NAME = Serializer

SRCS = main.cpp Serializer.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CPP) $(LINK_FLAGS) -o $@ $^

all: $(NAME)

%.o: %.cpp
	$(CPP) $(COMPILE_FLAGS) $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re test