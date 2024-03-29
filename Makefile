# OS DISCLAIMER #
.DELETE_ON_ERROR:

#UNAME_S := $(shell uname -s)

#ifeq ($(UNAME_S), Linux)
#	LIBS := -lm -lbsd -lX11 -lXext
#	MLX = mlx_linux/libmlx.a
#	MINILIBX = mlx_linux
#endif
#ifeq ($(UNAME_S), Darwin)
#	LIBS := -lz -framework OpenGL -framework AppKit
#	MINILIBX = mlx_ios
#	MLX = mlx_ios/libmlx.dylib
#endif

# FILE NAME #
NAME 		= ircserv

# PROYECT PATHS #
INCLUDES	= headers/
SRCPATH		= sources/

# USER FILES DEFINITION #
SRCFILES	= 	main.cpp						\
				IRC_Errors.cpp					\
				IRC_Utils.cpp					\
				IRC_Server.cpp					\
				IRC_User.cpp					\
				IRC_Channel.cpp 				\
				IRC_Message.cpp					\
				commands/IRC_DieCommand.cpp		\
				commands/IRC_InviteCommand.cpp	\
				commands/IRC_JoinCommand.cpp	\
				commands/IRC_KickCommand.cpp	\
				commands/IRC_KillCommand.cpp	\
				commands/IRC_ListCommand.cpp	\
				commands/IRC_ModeCommand.cpp	\
				commands/IRC_MOTDCommand.cpp	\
				commands/IRC_NamesCommand.cpp	\
				commands/IRC_NickCommand.cpp	\
				commands/IRC_NoticeCommand.cpp	\
				commands/IRC_OperCommand.cpp	\
				commands/IRC_PartCommand.cpp	\
				commands/IRC_PassCommand.cpp	\
				commands/IRC_PingCommand.cpp	\
				commands/IRC_PongCommand.cpp	\
				commands/IRC_PrivMsgCommand.cpp	\
				commands/IRC_QuitCommand.cpp	\
				commands/IRC_TopicCommand.cpp	\
				commands/IRC_UserCommand.cpp	\
				commands/IRC_WelcomeCommand.cpp	\
								

# SOURCES #
SOURCES		:= $(addprefix $(SRCPATH), $(SRCFILES))

# DEPENDENCIES
DEPENDENCIES = -MMD

# COMPILER AND FLAGS#
CXX = clang++
VERSION = --std=c++98 -pedantic
CXXFLAGS = -Wall -Wextra -Werror $(VERSION) -I$(INCLUDES) $(DEPENDENCIES)
LDFLAGS = $(LIBS)

ifdef DEBUG
	CXXFLAGS += -g3 -fsanitize=address
	LDFLAGS += -fsanitize=address
else
	CXXFLAGS += -O3
endif

# COLOUR DEFINITION #
RED 	:= \033[0;31m
YELLOW	:= \033[0;33m
BLUE 	:= \033[0;34m
GREEN 	:= \033[1;32m
MAGENTA	:= \033[0;35m
CYAN	:= \033[0;36m
WHITE	:= \033[0;37m
RESET 	:= \033[0m

OBJS = $(SOURCES:.cpp=.o)
DEPS = $(OBJS:.o=.d)

.cpp.o:
	@$(CXX) $(CXXFLAGS) -c $< -o $@
			@echo "$(RED)Compiling $(RESET) $(CXX) $(CXXFLAGS) $<. "

# CLEANING INSTRUCTION #
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)==========CREATING $(NAME)==========$(RESET)"
	@$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(WHITE)Done $(RESET)"
	@echo "  $(CYAN) ;D $(RESET) success linked app file "
	@echo "$(GREEN)==========WELLDONE==========$(RESET)"
	@echo "Success creating $(YELLOW)$(NAME) $(RESET)app file"
	@echo

info:
	$(info $(OBJS))

test:		all
	./$(NAME) 6667 "1234"

clean:
	@$(RM) $(OBJS)
	@echo "$(GREEN)==========REMOVED==========$(RESET)"
	@echo "Success normal cleaning"
	@echo ""

fclean: clean
	@$(RM) ${NAME} ${DEPS}
	@echo "$(GREEN)==========TOTALLY REMOVED==========$(RESET)"
	@echo "Success deepest cleaning of $(YELLOW)$(NAME)$(RESET) app and objects"
	@echo ""

re : fclean all

-include	$(DEPS)

.PHONY: all clean fclean re test
