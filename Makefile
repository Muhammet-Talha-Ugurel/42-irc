NAME		= irc
SRC			=  src/password/PasswordManager.cpp \
			   src/password/Password.cpp \
			   src/Server.cpp \
			   src/cmd/CommandManager.cpp \
			   src/cmd/CommandPass.cpp \
			   src/main.cpp \
			   src/user/User.cpp \
			   src/user/UserManager.cpp \
			   src/client/ClientManager.cpp \
			   src/client/Client.cpp
OBJ			= $(SRC:.cpp=.o)
CXX			= clang++
RM			= rm -rf
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98 -g

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
