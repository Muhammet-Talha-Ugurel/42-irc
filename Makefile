NAME		= ircserv
SRC			=  src/main.cpp \
			   src/Server.cpp \
			   src/channel/Channel.cpp \
			   src/channel/ChannelManager.cpp \
			   src/client/Client.cpp \
			   src/client/ClientManager.cpp \
			   src/cmd/CommandCap.cpp \
			   src/cmd/CommandJoin.cpp \
			   src/cmd/CommandKick.cpp \
			   src/cmd/CommandList.cpp \
			   src/cmd/CommandManager.cpp \
			   src/cmd/CommandMode.cpp \
			   src/cmd/CommandNames.cpp \
			   src/cmd/CommandNick.cpp \
			   src/cmd/CommandNotice.cpp \
			   src/cmd/CommandPart.cpp \
			   src/cmd/CommandPass.cpp \
			   src/cmd/CommandPing.cpp \
			   src/cmd/CommandPrivmsg.cpp \
			   src/cmd/CommandQuit.cpp \
			   src/cmd/CommandTopic.cpp \
			   src/cmd/CommandUser.cpp \
			   src/cmd/CommandUtils.cpp \
			   src/cmd/CommandWho.cpp \
			   src/cmd/CommandInvite.cpp \
			   src/cmd/Exception.cpp \
			   src/password/PasswordManager.cpp \
			   src/user/User.cpp \
			   src/user/UserManager.cpp
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
