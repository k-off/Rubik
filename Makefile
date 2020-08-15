# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pacovali <pacovali@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/15 02:47:19 by pacovali      #+#    #+#                  #
#    Updated: 2020/08/15 03:15:00 by pacovali      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = rubik

CXX = @clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -O3
SRC = main.cpp Rubik.class.cpp Solver.class.cpp
OBJS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^

clean:
	@$(RM) *.o *~ .DS_Store

fclean: clean
	@$(RM) $(NAME) ../.DS_Store

re: fclean all