CPP = c++
COMPILE_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g -c
LINK_FLAGS = 
NAME = ScalarConverter

SRCS = main.cpp ScalarConverter.cpp
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

.PHONY: all clean fclean re