# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/23 11:31:25 by irodrigo          #+#    #+#              #
#    Updated: 2023/06/30 14:23:27 by irodrigo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
NAME 		= PmergeMe

# PROYECT PATHS #
INCLUDES	:= includes
SRCPATH		:=

# USER FILES DEFINITION #
SRCFILES	:= main.cpp PmergeMe.cpp

# SOURCES #
SOURCES		:= $(addprefix $(SRCPATH), $(SRCFILES))

# DEPENDENCIES
DEPENDENCIES = -MD

# COMPILER AND FLAGS#
CXX = clang++
VERSION = --std=c++98 -pedantic
CXXFLAGS = -Wall -Wextra -Werror $(VERSION) -I$(INCLUDES) $(DEPENDENCIES)

ifdef DEBUG
	CXXFLAGS += -g3 -fsanitize=address
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
	@$(CXX) $(CXXFLAGS) ${OBJS} -o $(NAME)
	@echo "$(WHITE)Done $(RESET)"
	@echo "  $(CYAN) ;D $(RESET) success linked app file "
	@echo "$(GREEN)==========WELLDONE==========$(RESET)"
	@echo "Success creating $(YELLOW)$(NAME) $(RESET)app file"
	@echo

info:
	$(info $(OBJS))

test:		all
	./$(NAME)

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

#-include	$(DEPS)

.PHONY: all clean fclean re test
