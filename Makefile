NAME		= irc
SRC			= ./src/Server.cpp ./src/password/PasswordManager.cpp
OBJ			= $(SRC:.cpp=.o)
CXX			= clang++
RM			= rm -rf
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
