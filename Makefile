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
INCLUDES		= headers/
SRCPATH 		= sources/
COMMANDSPATH 	= commands/

# USER FILES DEFINITION #
SRCFILES		= 	\
					main.cpp						\
					IRC_Errors.cpp					\
					IRC_Utils.cpp					\
					IRC_Server.cpp					\
					IRC_User.cpp					\
					IRC_Channel.cpp 				\
					IRC_Message.cpp					\

SRCCOMMANDS 	=  \
					IRC_DieCommand.cpp				\
					IRC_InviteCommand.cpp			\
					IRC_JoinCommand.cpp				\
					IRC_KickCommand.cpp				\
					IRC_KillCommand.cpp				\
					IRC_ListCommand.cpp				\
					IRC_MOTDCommand.cpp				\
					IRC_NamesCommand.cpp			\
					IRC_NickCommand.cpp				\
					IRC_NoticeCommand.cpp			\
					IRC_OperCommand.cpp				\
					IRC_PartCommand.cpp				\
					IRC_PassCommand.cpp				\
					IRC_PingCommand.cpp				\
					IRC_PongCommand.cpp				\
					IRC_PrivMsgCommand.cpp			\
					IRC_QuitCommand.cpp				\
					IRC_TopicCommand.cpp			\
					IRC_UserCommand.cpp				\
					IRC_WelcomeCommand.cpp			\
								

# SOURCES #
SOURCES		:= $(addprefix $(SRCPATH), $(SRCFILES)  			\
				 $(addprefix $(COMMANDSPATH), $(SRCCOMMANDS)) 	\
			   )

# DEPENDENCIES
DEPENDENCIES = -MMD


# LIBCONSOLE

LIBPATH = ./libs
LIBS += -L $(LIBCONSOLEPATH) -l $(LIBCONSOLENAME)
INCLUDES += -I $(LIBCONSOLEPATH)/inc

LIBCONSOLENAME = console
LIBCONSOLEPATH = $(LIBPATH)/$(LIBCONSOLENAME)
LIBCONSOLE = $(LIBCONSOLEPATH)/lib$(LIBCONSOLENAME).a

# COMPILER AND FLAGS#
CXX 		= clang++
VERSION 	= --std=c++98 -pedantic
CXXFLAGS 	= -Wall -Wextra -Werror $(VERSION) -I$(INCLUDES) $(DEPENDENCIES)
LDFLAGS 	= $(LIBS)
SANITIZE 	= -fsanitize=address
SYMBOLS 	= -g3

ifdef DEBUG
	CXXFLAGS += $(SYMBOLS) $(SANITIZE)
	LDFLAGS += $(SANITIZE)
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

$(NAME): $(OBJS) $(LIBCONSOLE)
	echo "$(BLUE)==========CREATING $(NAME)==========$(RESET)"
	$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)
	echo "$(WHITE)Done $(RESET)"
	echo "  $(CYAN) ;D $(RESET) success linked app file "
	echo "$(GREEN)==========WELLDONE==========$(RESET)"
	echo "Success creating $(YELLOW)$(NAME) $(RESET)app file"
	echo

info:
	$(info $(OBJS))

$(LIBCONSOLE):
	make -C $(LIBCONSOLEPATH)

run:		debug
	./$(NAME) 6667 "1234"

clean:
	$(RM) $(OBJS)
	echo "$(GREEN)==========REMOVED==========$(RESET)"
	echo "Success normal cleaning"
	echo ""

fclean: 	clean
	$(RM) ${NAME} ${DEPS}
	echo "$(GREEN)==========TOTALLY REMOVED==========$(RESET)"
	echo "Success deepest cleaning of $(YELLOW)$(NAME)$(RESET) app and objects"
	echo ""

re: fclean all

debug: CXXFLAGS += $(SANITIZE) $(SYMBOLS)
debug: LDFLAGS += $(SANITIZE)
debug: all

-include	$(DEPS)

print:
	echo $(SOURCES)
	echo $(LIBCONSOLE)
	echo $(LIBCONSOLENAME)
	echo $(LIBCONSOLEPATH)

.PHONY: all clean fclean re test
.SILENT: clean fclean $(NAME)
